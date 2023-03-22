import { Controller, Get, Query, Redirect, Session } from '@nestjs/common';
import { LoginService } from './login.service';
import { ApiTags } from '@nestjs/swagger';
import { UserService } from 'src/user/user.service';

@ApiTags('login')
@Controller('login')
export class LoginController {
  constructor(private readonly loginService: LoginService, private readonly userService: UserService) {}

  @Get()
  @Redirect(
    `http://${process.env.REACT_APP_HOST}:${process.env.REACT_APP_PORT}`,
  )
  checkLogin(@Session() session: Record<string, any>) {
    if (!session.login) {
      return {
        url: this.loginService.getOAuthUrl(),
      };
    }
  }

  @Get('/anonymous')
  @Redirect(
    `http://${process.env.REACT_APP_HOST}:${process.env.REACT_APP_PORT}`,
  )
  async checkAnonymous(@Session() session: Record<string, any>) {
    if (!session.login) {
		session.login = true;
		const intra = 'anonymous'
		const usual_full_name = 'Anony Mous'

		const { ok, user } = await this.userService.getMe(intra);
		if (ok) {
			session.user = { intra, id: user.id };
		}
		else {
			const { ok, user } = await this.userService.createUser(
				intra,
				usual_full_name,
			);
			if (ok) {
				session.user = { intra, id: user.id };
			}
		}
    }
  }

  @Get('/redirect')
  @Redirect(
    `http://${process.env.REACT_APP_HOST}:${process.env.REACT_APP_PORT}`,
  )
  async login(
    @Session() session: Record<string, any>,
    @Query('code') code: string,
  ) {
    const { ok, error } = await this.loginService.login(session, code);
    if (!ok) {
      return { ok, error };
    }
  }
}
