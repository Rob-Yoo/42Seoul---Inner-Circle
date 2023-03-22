import {
  changeAvatarOutput,
  CheckNickNameOutput,
  CreateUserOutput,
  getMeOutput,
  getUserByIdOutput,
  getUserByNickNameOutput,
  UpdateUserDto,
  UpdateUserOutput,
} from './dtos/user.dto';
import { Injectable, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from './entities/user.entity';
import Avatar from './entities/avatar.entity';
import { gameMod } from 'src/game/dtos/game.dto';

@Injectable()
export class UserService {
  constructor(
    @InjectRepository(User) private readonly users: Repository<User>,
    @InjectRepository(Avatar) private readonly avatars: Repository<Avatar>,
  ) {}

  async getMe(intra: string): Promise<getMeOutput> {
    try {
      const user = await this.users.findOne({
        where: { intra },
      });
      if (user) {
        return { ok: true, user };
      }
      return { ok: false, error: 'User not Found' };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async createUser(
    intra: string,
    usual_full_name: string,
  ): Promise<CreateUserOutput> {
    try {
      const exists = await this.users.findOne({
        where: { intra },
      });
      if (exists) {
        return {
          ok: false,
          error: 'There is a user with that intraID already',
        };
      }
      const user = await this.users.save(
        this.users.create({ intra, usual_full_name }),
      );
      return { ok: true, user };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async getUserByNickName(nickname: string): Promise<getUserByNickNameOutput> {
    try {
      const user = await this.users.findOne({
        where: { nickname },
      });
      if (user) {
        return {
          ok: true,
          user,
        };
      }
      return { ok: false, error: 'Cannot find User.' };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async getUserById(id: number): Promise<getUserByIdOutput> {
    try {
      const user = await this.users.findOne({
        where: { id },
      });
      if (user) {
        return {
          ok: true,
          user,
        };
      }
      return { ok: false, error: 'Cannot find User.' };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async checkNickName(nickname: string): Promise<CheckNickNameOutput> {
    try {
      const exists = await this.users.findOne({
        where: { nickname },
      });
      if (exists) {
        return {
          ok: false,
          error: 'There is a user with that nickname already',
        };
      }
      return { ok: true };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async updateUser(
    id: number,
    updateData: UpdateUserDto,
  ): Promise<UpdateUserOutput> {
    try {
      await this.users.update(id, { ...updateData });
      return { ok: true };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async uploadAvatar(data: Buffer, filename: string) {
    const newFile = await this.avatars.save(
      this.avatars.create({ filename, data }),
    );
    return newFile;
  }

  async deleteAvatar(id: number) {
    await this.avatars.delete(id);
  }

  async getAvatarById(id: number) {
    const file = await this.avatars.findOne({ where: { id } });
    if (!file) {
      throw new NotFoundException();
    }
    return file;
  }

  async changeAvatar(
    id: number,
    imageBuffer: Buffer,
    filename: string,
  ): Promise<changeAvatarOutput> {
    try {
      const user = await this.users.findOne({ where: { id } });
      if (user.avatarId) {
        await this.deleteAvatar(user.avatarId);
      }
      const avatar = await this.uploadAvatar(imageBuffer, filename);
      await this.users.update(id, { avatarId: avatar.id });
      return { ok: true };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async getFriends(id: number) {
    try {
      const user = await this.users.findOne({
        where: { id },
        relations: ['friends'],
      });
      return { ok: true, friends: user.friends };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async addFriends(id: number, nickname: string) {
    try {
      const user1 = await this.users.findOne({
        where: { id },
        relations: ['friends'],
      });
      const user2 = await this.users.findOne({
        where: { nickname },
        relations: ['friends'],
      });

      if (!user1.friends.some((friend) => friend.id === user2.id)) {
        user1.friends.push(user2);
        user2.friends.push(user1);
        await this.users.save([user1, user2]);
      }
      return { ok: true };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async deleteFriends(id: number, nickname: string) {
    try {
      const user1 = await this.users.findOne({
        where: { id },
        relations: ['friends'],
      });
      const user2 = await this.users.findOne({
        where: { nickname },
        relations: ['friends'],
      });

      if (user1.friends.some((friend) => friend.id === user2.id)) {
        user1.friends = user1.friends.filter(
          (friend) => friend.id !== user2.id,
        );
        user2.friends = user2.friends.filter(
          (friend) => friend.id !== user1.id,
        );
        await this.users.save([user1, user2]);
      }
      return { ok: true };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async winGame(nickname: string, mod: gameMod) {
    try {
      const user = await this.users.findOne({
        where: { nickname },
      });
      if (!user) return { ok: false, error: 'User Not Found' };
      if (mod == gameMod.rankGame) user.r_win += 1;
      else user.f_win += 1;
      await this.users.update(user.id, {
        f_win: user.f_win,
        r_win: user.r_win,
      });
      return { ok: true, error: 'Success' };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async loseGame(nickname: string, mod: gameMod) {
    try {
      const user = await this.users.findOne({
        where: { nickname },
      });
      if (!user) return { ok: false, error: 'User Not Found' };
      if (mod == gameMod.rankGame) user.r_lose += 1;
      else user.f_lose += 1;
      await this.users.update(user.id, {
        f_lose: user.f_lose,
        r_lose: user.r_lose,
      });
      return { ok: true, error: 'Success' };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async getScoreByNickName(nickname: string) {
    try {
      const user = await this.users.findOne({
        where: { nickname },
      });
      if (user == undefined) {
        return {
          ok: false,
          error: 'User Not Found',
        };
      }
      const score = {
        f_win: user.f_win,
        f_lose: user.f_lose,
        r_win: user.r_win,
        r_lose: user.r_lose,
      };
      return { ok: true, score };
    } catch (error) {
      return { ok: false, error };
    }
  }
}
