import { Logger } from '@nestjs/common';
import { ApiResponse } from '@nestjs/swagger';
import {
  ConnectedSocket,
  MessageBody,
  OnGatewayConnection,
  OnGatewayDisconnect,
  OnGatewayInit,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Namespace, Socket } from 'socket.io';
import { UserService } from 'src/user/user.service';
import { GameDto, gameMod } from './dtos/game.dto';
import { GameService } from './game.service';

export interface Room {
  roomName: string;
  password: boolean;
}

export interface WaitingPlayer {
  waiting: boolean;
  socket: Socket;
  nickname: string;
}

let createdRooms: Room[] = [];
const onlineList = new Map<string, boolean>();

const GameDtoByRoomName = new Map<string, GameDto>();
const RoomNameByNickname = new Map<string, string>();
const NicknameBySocketId = new Map<string, string>();

const onClickSoloByNickname = new Map<string, boolean>();

const waitingPlayer: WaitingPlayer = {
  waiting: false,
  socket: undefined,
  nickname: undefined,
};

@ApiResponse({
  status: 200,
  description: 'returns game config',
})
@ApiResponse({ status: 403, description: 'Forbidden.' })
@WebSocketGateway({
  namespace: 'game',
  cors: {
    origin: [
      `http://${process.env.REACT_APP_HOST}:${process.env.REACT_APP_PORT}`,
    ],
    credentials: true,
  },
})
export class GamesGateway
  implements OnGatewayInit, OnGatewayConnection, OnGatewayDisconnect
{
  constructor(
    private gameService: GameService,
    private userService: UserService,
  ) {}
  private logger = new Logger('Game Gateway');

  @WebSocketServer() nsp: Namespace;

  afterInit() {
    this.nsp.adapter.on('delete-room', (roomName) => {
      this.logger.log(`${roomName} deleted!!!`);
      const deletedRoom = createdRooms.find(
        (createdRoom) => createdRoom.roomName === roomName,
      );
      if (!deletedRoom)
        return { success: false, payload: `${roomName} not found!` };

      this.nsp.emit('delete-room', deletedRoom.roomName);
      createdRooms = createdRooms.filter(
        (createdRoom) => createdRoom.roomName !== deletedRoom.roomName,
      ); // 유저가 생성한 room 목록 중에 삭제되는 room 있으면 제거
      return { success: true, payload: `${roomName} deleted!` };
    });

    this.logger.log('+=+=+=+=+=+= WebSever init Success +=+=+=+=+=+=');
  }

  handleConnection(@ConnectedSocket() socket: Socket) {
    this.logger.log(`${socket.id} +=+=+=+=+=+= Socket Connected +=+=+=+=+=+=`);
    //if (onlineList[socket.id])
  }

  async handleDisconnect(@ConnectedSocket() socket: Socket) {
    if (NicknameBySocketId[socket.id])
      this.logger.log(
        `${socket.id} (${
          NicknameBySocketId[socket.id]
        }) -=-=-=-=-=-= Socket Disconnected -=-=-=-=-=-=`,
      );
    else
      this.logger.log(
        `${socket.id} -=-=-=-=-=-= Socket Disconnected -=-=-=-=-=-=`,
      );

    const nickname = NicknameBySocketId[socket.id];
    NicknameBySocketId[socket.id] = undefined;

    let roomName: string = undefined;
    let gameDto: GameDto = undefined;
    if (nickname) {
      roomName = RoomNameByNickname[nickname];
      RoomNameByNickname[nickname] = undefined;
    }
    if (roomName) {
      gameDto = GameDtoByRoomName[roomName];
      GameDtoByRoomName[roomName] = undefined;
    }

    if (roomName && gameDto) {
      if (gameDto.p1.socket.id != socket.id) {
        await this.gameService.finishGame(gameDto, true);
      } else {
        await this.gameService.finishGame(gameDto, false);
      }
    }

    if (waitingPlayer.socket && socket.id == waitingPlayer.socket.id)
      waitingPlayer.waiting = false;

    onlineList[nickname] = false;
  }

  @SubscribeMessage('nickname')
  handleNickname(
    @ConnectedSocket() socket: Socket,
    @MessageBody() nickname: string,
  ) {
    this.logger.log(`Nickname Registration ${nickname}`);
    NicknameBySocketId[socket.id] = nickname;
    // 닉네임 등록시 online 으로 등록
    onlineList[nickname] = true;
    return { success: true, payload: `${nickname} change success!` };
  }

  @SubscribeMessage('clear')
  async handleClear(@ConnectedSocket() socket: Socket) {
    this.logger.log(
      `+=+=+=+=+=+=+=+=+= ${
        NicknameBySocketId[socket.id]
      } clear +=+=+=+=+=+=+=+=+=`,
    );

    const nickname = NicknameBySocketId[socket.id];
    if (!nickname) return;
    onClickSoloByNickname[nickname] = false;

    if (waitingPlayer.waiting == true && nickname == waitingPlayer.nickname) {
      this.logger.log(`${waitingPlayer.nickname} is clear ~~`);
      waitingPlayer.waiting = false;
      waitingPlayer.nickname = undefined;
    }
    const roomName = RoomNameByNickname[nickname];
    if (!roomName) {
      this.logger.log('clear: no roomName');
      return;
    }
    RoomNameByNickname[nickname] = undefined;
    socket.leave(roomName);
    const gameDto = GameDtoByRoomName[roomName];
    if (!gameDto) return;
    this.logger.log('a');
    if (gameDto.start && !gameDto.end) {
      this.logger.log('b');
      if (gameDto.p1.socket.id != socket.id) {
        await this.gameService.finishGame(gameDto, true);
      } else {
        await this.gameService.finishGame(gameDto, false);
      }
    }
    if (!gameDto) {
      this.logger.log('[clear] no gameDto');
      return;
    }
    GameDtoByRoomName[roomName] = undefined;

    clearInterval(gameDto.interval);
  }

  @SubscribeMessage('PaddleUp')
  handlePaddleUp(
    @ConnectedSocket() socket: Socket,
    @MessageBody() is_p1: boolean,
  ) {
    const nickname = NicknameBySocketId[socket.id];
    const roomName = RoomNameByNickname[nickname];
    const dto: GameDto = GameDtoByRoomName[roomName];
    if (!dto) return { success: false, payload: 'none game' };
    if (is_p1) dto.p1.padleUp = true;
    else dto.p2.padleUp = true;
    return { success: true, payload: `Paddle Up` };
  }

  @SubscribeMessage('PaddleDown')
  handlePaddleDown(
    @ConnectedSocket() socket: Socket,
    @MessageBody() is_p1: boolean,
  ) {
    const nickname = NicknameBySocketId[socket.id];
    const roomName = RoomNameByNickname[nickname];
    const dto: GameDto = GameDtoByRoomName[roomName];
    if (!dto) return { success: false, payload: 'none game' };
    if (is_p1) dto.p1.padleDown = true;
    else dto.p2.padleDown = true;
    return { success: true, payload: `Paddle Down` };
  }

  @SubscribeMessage('PaddleStop')
  handlePaddleStop(
    @ConnectedSocket() socket: Socket,
    @MessageBody() is_p1: boolean,
  ) {
    const nickname = NicknameBySocketId[socket.id];
    const roomName = RoomNameByNickname[nickname];
    const dto: GameDto = GameDtoByRoomName[roomName];
    if (!dto) return { success: false, payload: 'none game' };
    if (!dto) return;
    if (is_p1) {
      dto.p1.padleUp = false;
      dto.p1.padleDown = false;
    } else {
      dto.p2.padleUp = false;
      dto.p2.padleDown = false;
    }
    return { success: true, payload: `Paddle Stop` };
  }

  @SubscribeMessage('matching')
  async handleMatching(@ConnectedSocket() socket: Socket) {
    const nickname = NicknameBySocketId[socket.id];
    this.logger.log(`${nickname} call matching...`);

    this.logger.log(`${waitingPlayer.waiting}`);

    if (waitingPlayer.waiting) {
      if (nickname == waitingPlayer.nickname) return;

      const roomName = waitingPlayer.nickname + nickname;
      const Game: GameDto = this.gameService.init_game(
        waitingPlayer.socket, // p1
        waitingPlayer.nickname,
        roomName, // roomName
        gameMod.rankGame, // game mod
        this.nsp,
      );
      Game.p2.socket = socket;
      Game.p2.name = nickname;
      GameDtoByRoomName[roomName] = Game;

      createdRooms.push({ roomName: roomName, password: false }); // 유저가 생성한 room 목록에 추가

      const nickname_w = NicknameBySocketId[waitingPlayer.socket.id];
      RoomNameByNickname[nickname_w] = roomName;
      RoomNameByNickname[nickname] = roomName;

      socket.join(roomName); // 기존에 없던 room으로 join하면 room이 생성됨
      waitingPlayer.socket.join(roomName); // 기존에 없던 room으로 join하면 room이 생성됨

      const p1 = await this.userService.getUserByNickName(Game.p1.name);
      const p2 = await this.userService.getUserByNickName(Game.p2.name);

      const playerInfo = {
        p1: p1.user,
        p2: p2.user,
      };
      Game.start = true;
      this.nsp.in(roomName).emit('matching-success', playerInfo); // 대기실 방 생성을 연결된 클라들에게 알림
      this.logger.log('matching success!!!');

      waitingPlayer.waiting = false;
    } else {
      waitingPlayer.nickname = nickname;
      waitingPlayer.socket = socket;
      waitingPlayer.waiting = true;
      this.logger.log(`${nickname} matching waiting...`);
    }
    socket.broadcast.emit('refresh-status');
  }

  @SubscribeMessage('ready-rank')
  handleReadyRank(@ConnectedSocket() socket: Socket) {
    const nickname = NicknameBySocketId[socket.id];
    const roomName = RoomNameByNickname[nickname];
    if (!roomName) return { success: false, payload: `room not existed!` };
    const game: GameDto = GameDtoByRoomName[roomName];
    if (!game) return { success: false, payload: `game not existed!` };

    if (game.p1Ready === true && game.p2Ready == true)
      return { success: false, payload: `already started!` };

    if (game.p1.socket && socket.id === game.p1.socket.id) {
      game.p1Ready = true;
      this.logger.log(`Ready p1!!!`);
    } else if (game.p2.socket && socket.id === game.p2.socket.id) {
      game.p2Ready = true;
      this.logger.log(`Ready p2!!!`);
    }

    if (game.p1Ready === true && game.p2Ready == true) {
      game.start = true;
      game.p1.socket.emit('start-game', true);
      game.p2.socket.emit('start-game', false);
      this.gameService.gameLoop(game);
      this.logger.log(`Game Start!!!`);
      socket.broadcast.emit('refresh-status');
    }
  }

  @SubscribeMessage('click-solo')
  handleClickSolo(@ConnectedSocket() socket: Socket) {
    const nickname = NicknameBySocketId[socket.id];
    if (!nickname) return { success: false, payload: 'click-solo error' };
    onClickSoloByNickname[nickname] = true;
    return { success: true, payload: 'click-solo' };
  }

  @SubscribeMessage('ready-solo')
  handleReadySolo(@ConnectedSocket() socket: Socket) {
    const nickname = NicknameBySocketId[socket.id];
    if (!nickname) return { success: false, payload: 'nickname error' };
    if (RoomNameByNickname[nickname]) {
      this.logger.log('already solo mod playing');
      return { success: false, payload: 'already solo mod playing' };
    } // 여기 조건문 달아서 중복 호출 막음
    if (!onClickSoloByNickname[nickname])
      return { success: false, payload: 'not solo page' };

    this.logger.log(`Solo Ready !!!`);
    const Game: GameDto = this.gameService.init_test(
      socket,
      socket.id,
      gameMod.soloGame,
    );
    Game.start = true;
    GameDtoByRoomName[Game.roomName] = Game;
    RoomNameByNickname[nickname] = Game.roomName;

    socket.broadcast.emit('refresh-status');

    this.gameService.gameLoop(GameDtoByRoomName[Game.roomName]);
  }

  @SubscribeMessage('end-game')
  handleEndGame(@ConnectedSocket() socket: Socket) {
    const nickname_p1 = NicknameBySocketId[socket.id];
    const roomName = RoomNameByNickname[nickname_p1];
    const gameDto = GameDtoByRoomName[roomName];
    // RoomName, GameDto Map 초기화
    if (roomName && gameDto) {
      RoomNameByNickname[nickname_p1] = undefined;
      if (gameDto.gameMod != gameMod.soloGame)
        RoomNameByNickname[NicknameBySocketId[gameDto.p2.socket.id]] =
          undefined;
      GameDtoByRoomName[roomName] = undefined;
    }
    // createdRoom 배열 초기화
    const deletedRoom = createdRooms.find(
      (createdRoom) => createdRoom.roomName === roomName,
    );
    if (!deletedRoom)
      return { success: false, payload: `${roomName} not found!` };

    this.nsp.emit('delete-room', deletedRoom.roomName);
    createdRooms = createdRooms.filter(
      (createdRoom) => createdRoom.roomName !== deletedRoom.roomName,
    ); // 유저가 생성한 room 목록 중에 삭제되는 room 있으면 제거

    socket.broadcast.emit('refresh-status');
    return { success: true, payload: `${roomName} deleted!` };
  }

  @SubscribeMessage('find-room')
  handleFindRoom(@MessageBody() nickname: string) {
    const roomName = RoomNameByNickname[nickname];
    if (!roomName)
      return { success: false, payload: `${nickname} doesn't have a room` };
    return { success: true, payload: roomName };
  }

  @SubscribeMessage('room-list')
  handleRoomList() {
    const activeRooms: Room[] = [];
    createdRooms?.forEach((room) => {
      const game = GameDtoByRoomName[room.roomName];
      if (game?.p2?.name) {
        activeRooms.push(room);
      }
    });
    return activeRooms;
  }

  @SubscribeMessage('create-room')
  async handleCreateRoom(
    @ConnectedSocket() socket: Socket,
    @MessageBody()
    room: {
      roomName: string;
      password: string;
    },
  ) {
    const exists = createdRooms.find(
      (createdRoom) => createdRoom.roomName === room.roomName,
    );
    if (exists) {
      return {
        success: false,
        payload: `${room.roomName} room already existed!`,
      };
    }

    this.logger.log('++=+=++ created Room +=++=+=');
    this.logger.log(`++=+=+${NicknameBySocketId[socket.id]}+=+++=`);

    const Game: GameDto = this.gameService.init_game(
      socket, // p1
      NicknameBySocketId[socket.id],
      room.roomName, // roomName
      gameMod.normalGame, // game mod
      this.nsp,
    );
    if (room.password) {
      this.logger.log(room.password);
      Game.gameMod = gameMod.passwordGame;
      Game.password = await this.gameService.hashPassword(room.password);
    }
    GameDtoByRoomName[room.roomName] = Game;

    socket.join(room.roomName); // 기존에 없던 room으로 join하면 room이 생성됨
    if (room.password)
      createdRooms.push({
        roomName: room.roomName,
        password: true,
      });
    // 유저가 생성한 room 목록에 추가
    else createdRooms.push({ roomName: room.roomName, password: false }); // 유저가 생성한 room 목록에 추가
    RoomNameByNickname[Game.p1.name] = room.roomName;

    this.nsp.emit('create-room', room.roomName); // 대기실 방 생성

    socket.broadcast.emit('refresh-status');
    return { success: true, payload: room.roomName };
  }

  @SubscribeMessage('join-room')
  async handleEnterRoom(
    @ConnectedSocket() socket: Socket,
    @MessageBody() roomName: string,
  ) {
    const exists = createdRooms.find(
      (createdRoom) => createdRoom.roomName === roomName,
    );
    if (exists == undefined) {
      return { success: false, payload: `${roomName} not found!` };
    }

    const Game: GameDto = GameDtoByRoomName[roomName];
    if (!Game) return { success: false, payload: `game not existed!` };
    if (Game.p2.name)
      return {
        success: false,
        payload: `${NicknameBySocketId[socket.id]} is not player!`,
      };

    this.logger.log('+=+=+=+=+=+= join Room +=+=+=+=+=+=');

    socket.join(roomName); // join room
    Game.p2.socket = socket;
    Game.p2.name = NicknameBySocketId[socket.id];
    RoomNameByNickname[Game.p2.name] = roomName;

    const p1 = await this.userService.getUserByNickName(
      NicknameBySocketId[Game.p1.socket.id],
    );
    const p2 = await this.userService.getUserByNickName(
      NicknameBySocketId[Game.p2.socket.id],
    );

    const playerInfo = {
      p1: p1.user,
      p2: p2.user,
    };

    this.logger.log(`p1: ${Game.p1.name}, p2: ${Game.p2.name}`);
    Game.p1.socket.emit('matching-success', playerInfo);
    socket.emit('matching-success', playerInfo);

    Game.start = true;

    socket.broadcast.emit('refresh-status');
    return { success: true, payload: roomName };
  }

  @SubscribeMessage('watching')
  async handleWatching(@ConnectedSocket() socket: Socket) {
    const nickname = NicknameBySocketId[socket.id];
    const roomName = RoomNameByNickname[nickname];
    const Game = GameDtoByRoomName[roomName];

    const p1 = await this.userService.getUserByNickName(Game.p1.name);
    const p2 = await this.userService.getUserByNickName(Game.p2.name);

    const playerInfo = {
      p1: p1.user,
      p2: p2.user,
    };

    return playerInfo;
  }

  @SubscribeMessage('watch-room')
  async handleJoinRoom(
    @ConnectedSocket() socket: Socket,
    @MessageBody()
    room: {
      roomName: string;
      password: string;
    },
  ) {
    this.logger.log(`watch-room ${NicknameBySocketId[socket.id]}`);
    const exists = createdRooms.find(
      (createdRoom) => createdRoom.roomName === room.roomName,
    );
    if (exists == undefined) {
      return { success: false, payload: `${room.roomName} not found!` };
    }

    const Game: GameDto = GameDtoByRoomName[room.roomName];
    const isMatch = await this.gameService.verifyPassword(
      room.password,
      Game.password,
    );
    if (Game.gameMod === gameMod.passwordGame && !isMatch) {
      return { success: false, payload: `${room.roomName} password wrong!` };
    }

    socket.join(room.roomName); // join room
    const nickname = NicknameBySocketId[socket.id];
    RoomNameByNickname[nickname] = room.roomName;
    socket.broadcast.emit('refresh-status');

    return { success: true, payload: room.roomName };
  }

  @SubscribeMessage('leave-room')
  handleLeaveRoom(
    @ConnectedSocket() socket: Socket,
    @MessageBody() roomName: string,
  ) {
    socket.leave(roomName); // leave room
    const nickname = NicknameBySocketId[socket.id];
    RoomNameByNickname[nickname] = undefined;

    return { success: true, payload: roomName };
  }

  @SubscribeMessage('check-status')
  handleOnline(@MessageBody() nickname: string) {
    const roomName = RoomNameByNickname[nickname];
    if (!roomName) return false;
    const gameDto = GameDtoByRoomName[roomName];
    if (!gameDto) return false;
    return true;
  }
}
