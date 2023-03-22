import { Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { User } from 'src/user/entities/user.entity';
import { Repository } from 'typeorm';
import { SolapiMessageService } from 'solapi';
import { tfaModuleOptions } from './tfa.interfaces';
import { UserService } from 'src/user/user.service';
import { SendSMSOutput } from './dtos/tfa.dto';

@Injectable()
export class TfaService {
  constructor(
    @InjectRepository(User) private readonly users: Repository<User>,
    @Inject('tfa_options') private readonly options: tfaModuleOptions,
    private readonly userService: UserService,
  ) {}

  async sendSMS(id: number, phone: string): Promise<SendSMSOutput> {
    try {
      const messageService = new SolapiMessageService(
        this.options.apiKey,
        this.options.secretKey,
      );

      const code = Math.round(Math.random() * 1000000)
        .toString()
        .padStart(6, '0');
      await this.userService.updateUser(id, { phone, code });
      messageService.sendOne({
        to: phone,
        from: this.options.sender,
        text: `your verification code is ${code}.`,
      });
      return { ok: true };
    } catch (error) {
      return { ok: false, error };
    }
  }

  async verifyUser(id: number, code: string) {
    try {
      const userCode = await this.users.findOne({
        where: { id },
        select: ['code'],
      });
      if (userCode.code === code) {
        await this.userService.updateUser(id, { verified: true });
        return { ok: true };
      }
      return { ok: false, error: 'Incorrect verification code' };
    } catch (e) {
      return { ok: false, error: "Couldn't create account" };
    }
  }
}
