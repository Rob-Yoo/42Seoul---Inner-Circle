import { User } from './../user/entities/user.entity';
import { Socket } from 'socket.io';
import {
  WebSocketGateway,
  SubscribeMessage,
  MessageBody,
  ConnectedSocket,
  OnGatewayDisconnect,
  OnGatewayConnection,
  OnGatewayInit,
} from '@nestjs/websockets';
import { UserService } from 'src/user/user.service';
import * as bcrypt from 'bcrypt';

// private: 비공개, protected: 비번으로 잠김
export interface ChannelInfo {
  name: string;
  owner: string; // socket id
  admins: Set<string>; // socket id
  members: Set<string>; // socket id
  private: boolean;
  password: string;
  channelMute: Map<string, number>; // socket id
  banList: Map<string, number>; // socket id
}

export interface UserInfo {
  user: User;
  channel: string;
  userMute: Map<string, number>; // socket id
}

export interface SocketInputDto {
  author?: string; // nickname
  target?: string; // nickname or channel name
  message?: string;
  password?: string;
}

export interface SocketOutputDto {
  author?: string; // nickname
  target?: string; // nickname or channel name
  message?: string;
  user?: User;
}

@WebSocketGateway({
  namespace: 'chat',
  cors: {
    origin: [
      `http://${process.env.REACT_APP_HOST}:${process.env.REACT_APP_PORT}`,
    ],
    credentials: true,
  },
})
export class ChatGateway
  implements OnGatewayInit, OnGatewayConnection, OnGatewayDisconnect
{
  channels: Map<string, ChannelInfo> = new Map<string, ChannelInfo>(); // key: channel name
  users: Map<string, UserInfo> = new Map<string, UserInfo>(); // key: socket id
  sockets: Map<string, string> = new Map<string, string>(); // key: nick name, value: socket id

  constructor(private readonly userService: UserService) {}

  afterInit() {
    this.channels.clear();
    this.users.clear();
    this.sockets.clear();

    console.log('웹소켓 서버 초기화 ✅');
  }

  // 처음 접속시 user에 추가
  async handleConnection(@ConnectedSocket() socket: Socket) {
    const { nickname } = socket.handshake.query;

    // 중복 접속 불허
    if (typeof nickname === 'string' && !this.users.has(nickname)) {
      const { user } = await this.userService.getUserByNickName(nickname);
      this.users.set(socket.id, {
        user,
        channel: null,
        userMute: new Map<string, number>(),
      });
      this.sockets.set(nickname, socket.id);
      console.log(`${socket.id}(${nickname}) 소켓 연결`);
      socket.broadcast.emit('refresh-status');
    } else {
      socket.disconnect();
    }
  }

  // 연결 끊길때 user에서 제거
  handleDisconnect(@ConnectedSocket() socket: Socket) {
    const { nickname } = socket.handshake.query;

    if (typeof nickname === 'string' && this.sockets.has(nickname)) {
      this.users.delete(socket.id);
      this.sockets.delete(nickname);
      this.channels.forEach((channel) => {
        this.part(channel.name, socket.id);
      });
    }
    console.log(`${socket.id} 소켓 연결 해제 ❌`);
    socket.broadcast.emit('refresh-status');
  } // 채널에서 나갔다고 알려줘야 함.

  async hashPassword(password: string): Promise<string> {
    if (!password) {
      return '';
    }
    const saltRounds = 10;
    const salt = await bcrypt.genSalt(saltRounds);
    const hashedPassword = await bcrypt.hash(password, salt);
    return hashedPassword;
  }

  async verifyPassword(
    password: string,
    hashedPassword: string,
  ): Promise<boolean> {
    if (!password && !hashedPassword) return true;
    const isMatch = await bcrypt.compare(password, hashedPassword);
    return isMatch;
  }

  @SubscribeMessage('channel-list')
  handleChannelList() {
    const channelList = [];

    this.channels.forEach((channel) => {
      if (!channel.private) {
        // private일때 안보냄
        const channelObj = {
          name: channel.name,
          // hidden: channel.private,
          password: channel.password !== '',
        };
        channelList.push(channelObj);
      }
    });
    return channelList;
  }

  @SubscribeMessage('channel-msg')
  handleChannelMsg(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const { author, target } = input;
    const { user } = this.users.get(this.sockets.get(author));

    if (author !== target) {
      if (this.channels.has(target)) {
        const { members, channelMute } = this.channels.get(target);
        members.forEach((member) => {
          if (member !== socket.id) {
            const now = new Date().getTime();
            const authorID: string = this.sockets.get(author); // author -> this->sockets.get(author)

            if (channelMute.has(authorID) && now < channelMute.get(authorID)) {
              return;
            }
            const { userMute } = this.users.get(member);
            if (userMute.has(authorID) && now < userMute.get(authorID)) {
              return;
            }
            socket.to(member).emit('channel-msg', { ...input, user });
          }
        });
      }
    }
    return { ...input, user };
  }

  @SubscribeMessage('channel-mute')
  muteByChannel(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const channel = this.users.get(socket.id).channel;

    if (input.author !== input.target) {
      if (this.sockets.has(input.target)) {
        const targetSocket = this.sockets.get(input.target);
        if (
          this.checkAdmin(input.author, channel) && // socket.id -> input.author
          !this.checkAdmin(input.target, channel) // targetSocket -> input.target
        ) {
          const validTime = new Date().getTime() + 300_000;
          this.channels.get(channel).channelMute.set(targetSocket, validTime);
          const output = {
            author: 'server',
            target: input.target,
            message: `${input.target} is muted`,
          };
          this.channels.get(channel).members.forEach((member) => {
            if (member !== socket.id) {
              socket.to(member).emit('notice', output);
            }
          });
          return output;
        }
      }
    }
    return {
      author: 'server',
      target: null,
      message: `fails to mute ${input.target}`,
    };
  }

  @SubscribeMessage('channel-unmute')
  unmuteByChannel(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const channel = this.users.get(socket.id).channel;

    if (input.author !== input.target) {
      if (this.sockets.has(input.target)) {
        const targetSocket = this.sockets.get(input.target);
        if (
          this.checkAdmin(input.author, channel) && // socket.id -> input.author
          !this.checkAdmin(input.target, channel) // targetSocket -> input.target
        ) {
          this.channels.get(channel).channelMute.delete(targetSocket);
          const output = {
            author: 'server',
            target: input.target,
            message: `${input.target} is unmuted`,
          };
          this.channels.get(channel).members.forEach((member) => {
            if (member !== socket.id) {
              socket.to(member).emit('notice', output);
            }
          });
          return output;
        }
      }
    }
    return {
      author: 'server',
      target: null,
      message: `fails to unmute ${input.target}`,
    };
  }

  @SubscribeMessage('direct-msg')
  handleDirectMsg(
    @ConnectedSocket() socket: Socket,
    @MessageBody() chat: SocketInputDto,
  ): SocketOutputDto {
    const { author, target } = chat;
    const { user } = this.users.get(this.sockets.get(author));

    if (author !== target) {
      if (this.sockets.has(target)) {
        const targetSocket = this.sockets.get(target);
        const { userMute } = this.users.get(targetSocket);
        const now = new Date().getTime();
        const authorID: string = this.sockets.get(author); // author -> this->sockets.get(author)
        if (!(userMute.has(authorID) && now < userMute.get(authorID))) {
          socket.to(targetSocket).emit('direct-msg', { ...chat, user });
        }
      }
    }
    return { ...chat, user };
  }

  @SubscribeMessage('direct-mute')
  muteByUser(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    if (input.author !== input.target) {
      if (this.users.has(socket.id) && this.sockets.has(input.target)) {
        const validTime = new Date().getTime() + 300_000;
        this.users
          .get(socket.id)
          .userMute.set(this.sockets.get(input.target), validTime);
        return {
          author: 'server',
          target: input.target,
          message: `${input.target} is muted`,
        };
      }
    }
    return {
      author: 'server',
      target: null,
      message: `fails to mute ${input.target}`,
    };
  }

  @SubscribeMessage('direct-unmute')
  unmuteByUser(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    if (input.author !== input.target) {
      if (this.users.has(socket.id) && this.sockets.has(input.target)) {
        this.users
          .get(socket.id)
          .userMute.delete(this.sockets.get(input.target));
        return {
          author: 'server',
          target: input.target,
          message: `${input.target} is unmuted`,
        };
      }
    }
    return {
      author: 'server',
      target: null,
      message: `fails to unmute ${input.target}`,
    };
  }

  part(channelName: string, userSocket: string) {
    if (channelName && this.channels.has(channelName)) {
      const channel = this.channels.get(channelName);

      channel.admins.delete(userSocket);
      channel.members.delete(userSocket);
      if (userSocket === channel.owner) {
        if (channel.admins.size > 0) {
          channel.owner = channel.admins.values().next().value;
        } else if (channel.members.size > 0) {
          channel.owner = channel.members.values().next().value;
        } else {
          this.channels.delete(channelName);
        }
      }
      return true;
    }
    return false;
  }

  @SubscribeMessage('join-channel')
  async joinChannel(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): Promise<SocketOutputDto> {
    if (this.channels.has(input.target)) {
      const channel = this.channels.get(input.target);
      const now = new Date().getTime();
      const isMatch = await this.verifyPassword(
        input.password,
        channel.password,
      );

      if (
        !(
          channel.banList.has(socket.id) && now < channel.banList.get(socket.id)
        ) &&
        isMatch
      ) {
        channel.members.add(socket.id);
      } else {
        return {
          author: 'server',
          target: undefined, // null -> undefined
          message: `fails to join channel: ${input.target}`,
        };
      }
    } else {
      const admins = new Set<string>();
      const members = new Set<string>();
      const banList = new Map<string, number>();
      const channelMute = new Map<string, number>();
      admins.add(socket.id);
      members.add(socket.id);
      this.channels.set(input.target, {
        name: input.target,
        owner: socket.id,
        admins,
        members,
        banList,
        private: false,
        password: '',
        channelMute,
      });
    }
    const user = this.users.get(socket.id);
    this.part(user.channel, socket.id);
    user.channel = input.target;
    const output = {
      author: 'server',
      target: input.target,
      message: `${input.author} joined the channel: ${input.target}`,
    };
    this.channels.get(input.target).members.forEach((member) => {
      if (member !== socket.id) {
        socket.to(member).emit('notice', output);
      }
    });
    return output;
  }

  @SubscribeMessage('leave-channel')
  leaveChannel(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const user = this.users.get(socket.id);
    const leaved = this.part(user.channel, socket.id);
    if (leaved) {
      user.channel = undefined; // null -> undefined
      const output = {
        author: 'server',
        target: input.target,
        message: `${input.author} left for the channel: ${input.target}`, // leave channel: ${input.target} -> ${input.author} left for the channel: ${input.target}
      };
      this.channels.get(input.target).members.forEach((member) => {
        if (member !== socket.id) {
          socket.to(member).emit('notice', output);
        }
      });
      return output;
    }
    return {
      author: 'server',
      target: undefined, // null -> undefined
      message: `fails to leave channel: ${input.target}`,
    };
  }

  checkOwner(userSocket: string, channel: string) {
    if (this.sockets.has(userSocket) && this.channels.has(channel)) {
      const { owner } = this.channels.get(channel);
      if (this.sockets.get(userSocket) === owner) {
        // userSocket -> this.sockets.get(userSocket)
        return true;
      }
    }
    return false;
  }

  checkAdmin(userSocket: string, channel: string) {
    if (this.sockets.has(userSocket) && this.channels.has(channel)) {
      const { owner, admins } = this.channels.get(channel);
      if (
        this.sockets.get(userSocket) === owner ||
        admins.has(this.sockets.get(userSocket))
      ) {
        // userSocket -> this.sockets.get(userSocket)
        return true;
      }
    }
    return false;
  }

  @SubscribeMessage('authorize')
  authorizeUser(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const channel = this.users.get(socket.id).channel;

    if (input.author !== input.target) {
      if (
        this.checkOwner(input.author, channel) && // socket.id -> input.author
        this.sockets.has(input.target)
      ) {
        this.channels.get(channel).admins.add(this.sockets.get(input.target));
        const output = {
          author: 'server',
          target: input.target,
          message: `${input.target} is admin now`,
        };
        this.channels.get(channel).members.forEach((member) => {
          if (member !== socket.id) {
            socket.to(member).emit('notice', output);
          }
        });
        return output;
      }
    }
    return {
      author: 'server',
      target: null,
      message: `fails to authorize ${input.target}`,
    };
  }

  @SubscribeMessage('deauthorize')
  unauthorizeUser(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const channel = this.users.get(socket.id).channel;

    if (input.author !== input.target) {
      if (
        this.checkOwner(input.author, channel) && // socket.id -> input.author
        this.sockets.has(input.target)
      ) {
        this.channels.get(channel).admins.add(this.sockets.get(input.target));
        const output = {
          author: 'server',
          target: input.target,
          message: `${input.target} is admin now`,
        };
        this.channels.get(channel).members.forEach((member) => {
          if (member !== socket.id) {
            socket.to(member).emit('notice', output);
          }
        });
        return output;
      }
    }
    return {
      author: 'server',
      target: null,
      message: `fails to deauthorize ${input.target}`,
    };
  }

  @SubscribeMessage('channel-ban')
  kickUser(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const channel = this.users.get(socket.id).channel;

    if (input.author !== input.target) {
      if (this.sockets.has(input.target)) {
        const targetSocket = this.sockets.get(input.target);
        if (
          this.checkAdmin(input.author, channel) && // socket.id -> input.author
          !this.checkAdmin(input.target, channel) // targetSocket -> input.target
        ) {
          this.part(channel, targetSocket);
          this.users.get(targetSocket).channel = targetSocket;
          const output = {
            author: 'server',
            target: input.target,
            message: `${input.target} is kicked from channel`,
          };
          this.channels.get(channel).members.forEach((member) => {
            if (member !== socket.id) {
              socket.to(member).emit('notice', output);
            }
          });
          this.banUser(socket, input);
          socket
            .to(this.sockets.get(input.target))
            .emit('leave-channel', output);
          return output;
        }
      }
    }
    return {
      author: 'server',
      target: null,
      message: `fails to kick ${input.target} from channel`,
    };
  }

  banUser(socket: Socket, input: SocketInputDto) {
    const channel = this.users.get(socket.id).channel;

    if (input.author !== input.target) {
      if (this.sockets.has(input.target)) {
        const targetSocket = this.sockets.get(input.target);
        if (
          this.checkAdmin(input.author, channel) && // socket.id -> input.author
          !this.checkAdmin(input.target, channel) // targetSocket -> input.target
        ) {
          const validTime = new Date().getTime() + 300_000;
          this.channels.get(channel).banList.set(targetSocket, validTime);
        }
      }
    }
  }

  // 서버에서 처리하는게 나을듯(따로 보내줄 명령어 안만들고)
  unbanUser(socket: Socket, input: SocketInputDto) {
    const channel = this.users.get(socket.id).channel;

    if (input.author !== input.target) {
      if (this.sockets.has(input.target)) {
        const targetSocket = this.sockets.get(input.target);
        if (
          this.checkAdmin(input.author, channel) && // socket.id -> input.author
          !this.checkAdmin(input.target, channel) // targetSocket -> input.target
        ) {
          this.channels.get(channel).banList.delete(targetSocket);
        }
      }
    }
  }

  @SubscribeMessage('password')
  async setPassword(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): Promise<SocketOutputDto> {
    const channel = this.users.get(socket.id).channel;

    if (this.checkOwner(input.author, channel)) {
      // socket.id -> input.author
      const hashedPassword = await this.hashPassword(input.password);
      this.channels.get(channel).password = hashedPassword;
      const output = {
        author: 'server',
        target: input.target,
        message: `password is set on ${input.target}`,
      };
      this.channels.get(channel).members.forEach((member) => {
        if (member !== socket.id) {
          socket.to(member).emit('notice', output);
        }
      });
      return output;
    }
    return {
      author: 'server',
      target: null,
      message: `fails to set password on ${input.target}`,
    };
  }

  @SubscribeMessage('private')
  setPrivate(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const channel = this.users.get(socket.id).channel;
    if (this.checkOwner(input.author, channel)) {
      // socket.id -> input.author
      this.channels.get(channel).private = true;
      const output = {
        author: 'server',
        target: input.target,
        message: `${input.target} is set to private`,
      };
      this.channels.get(channel).members.forEach((member) => {
        if (member !== socket.id) {
          socket.to(member).emit('notice', output);
        }
      });
      return output;
    }
    return {
      author: 'server',
      target: null,
      message: `fails to private ${input.target}`,
    };
  }

  @SubscribeMessage('deprivate')
  unsetPrivate(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const channel = this.users.get(socket.id).channel;

    if (this.checkOwner(input.author, channel)) {
      // socket.id -> input.author
      this.channels.get(channel).private = false;
      const output = {
        author: 'server',
        target: input.target,
        message: `${input.target} is set to deprivate`,
      };
      this.channels.get(channel).members.forEach((member) => {
        if (member !== socket.id) {
          socket.to(member).emit('notice', output);
        }
      });
      return output;
    }
    return {
      author: 'server',
      target: null,
      message: `fails to deprivate ${input.target}`,
    };
  }

  @SubscribeMessage('be-friend')
  addFriend(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const { user } = this.users.get(this.sockets.get(input.author));

    if (this.sockets.has(input.target)) {
      const output = {
        author: input.author,
        target: input.target,
        message: `${input.author} wants to be friend with you`,
        user,
      };
      const targetSocket: string = this.sockets.get(input.target);
      socket.to(targetSocket).emit('be-friend', output);
      return {
        author: 'server',
        target: null,
        message: `send friend request to ${input.target}`,
      };
    }
    return {
      author: 'server',
      target: null,
      message: `fails to send friend request to ${input.target}`,
    };
  }

  @SubscribeMessage('res-friend')
  checkFriend(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    if (input.target) {
      const output = {
        author: 'server',
        target: null,
        message: input.message
          ? `${input.author} become friend with you`
          : `${input.author} rejected your request`,
      };
      const targetSocket: string = this.sockets.get(input.target);
      socket.to(targetSocket).emit('notice', output);
      return {
        author: 'server',
        target: null,
        message: `you ${
          input.message ? 'accepted' : 'rejected'
        } friend request from ${input.target}`,
      };
    }
    return {
      author: 'server',
      target: null,
      message: `fails to response to ${input.target}`,
    };
  }

  @SubscribeMessage('get-profile')
  getProfile(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const { user } = this.users.get(this.sockets.get(input.target));

    return {
      author: 'server',
      target: null,
      message: `get ${input.target}'s profile`,
      user,
    };
  }

  @SubscribeMessage('check-status')
  checkStatus(
    @ConnectedSocket() socket: Socket,
    @MessageBody() nickname: string,
  ): boolean {
    if (this.users.has(this.sockets.get(nickname))) return true;
    return false;
  }

  @SubscribeMessage('invite')
  inviteGame(
    @ConnectedSocket() socket: Socket,
    @MessageBody() input: SocketInputDto,
  ): SocketOutputDto {
    const { user } = this.users.get(this.sockets.get(input.author));

    if (this.sockets.has(input.target)) {
      const output = {
        author: input.author,
        target: input.target,
        message: `you are invited to ${input.author}`,
        user,
      };
      socket.to(this.sockets.get(input.target)).emit('invite', output);
      return {
        author: 'server',
        target: null,
        message: `send invitation to ${input.target}`,
      };
    }
    return {
      author: 'server',
      target: null,
      message: `fails to send friend request to ${input.target}`,
    };
  }
}
