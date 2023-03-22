import { LoginOutput } from './dtos/login.dto';
import { Inject, Injectable } from '@nestjs/common';
import { loginModuleOptions } from './login.interfaces';
import { User } from 'src/user/entities/user.entity';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { UserService } from 'src/user/user.service';

@Injectable()
export class LoginService {
  constructor(
    @Inject('login_options') private readonly options: loginModuleOptions,
    @InjectRepository(User) private readonly users: Repository<User>,
    private readonly userService: UserService,
  ) {}

  getOAuthUrl(): string {
    return `${this.options.baseUrl}/oauth/authorize?client_id=${
      this.options.uid
    }&redirect_uri=${encodeURIComponent(
      this.options.redirect,
    )}&response_type=code`;
  }

  async login(
    session: Record<string, any>,
    code: string,
  ): Promise<LoginOutput> {
    try {
      // get token
      const form = new FormData();
      form.append('grant_type', 'authorization_code');
      form.append('client_id', this.options.uid);
      form.append('client_secret', this.options.secret);
      form.append('code', code);
      form.append('redirect_uri', this.options.redirect);

      const getToken = await fetch(`${this.options.baseUrl}/oauth/token`, {
        method: 'POST',
        body: form,
      });
      const { access_token } = await getToken.json();
      if (!access_token) {
        return { ok: false, error: 'Fail to get token' };
      }

      // get me
      const getMe = await fetch(`${this.options.baseUrl}/v2/me`, {
        method: 'GET',
        headers: {
          Authorization: 'Bearer ' + access_token,
          'Content-Type': 'application/json; charset=utf-8',
        },
      });
      const { login: intra, usual_full_name } = await getMe.json();

      if (!intra || !usual_full_name) {
        return { ok: false, error: 'Fail to call get me' };
      }

      session.login = true;
      const { ok, user } = await this.userService.getMe(intra);
      if (ok) {
        session.user = { intra, id: user.id };
      } else {
        const { ok, user } = await this.userService.createUser(
          intra,
          usual_full_name,
        );
        if (ok) {
          session.user = { intra, id: user.id };
        }
      }
      return { ok: session.login };
    } catch (error) {
      return { ok: false, error };
    }
  }
}
