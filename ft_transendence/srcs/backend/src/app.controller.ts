import { Controller, Get, Session } from '@nestjs/common';
import { AppService } from './app.service';
import { ApiTags } from '@nestjs/swagger';

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get()
  getHello(): string {
    return this.appService.getHello();
  }

  @Get('test')
  test(): string {
    return 'test';
  }

  @ApiTags('login')
  @Get('/logout')
  async logout(@Session() session: Record<string, any>) {
    session.login = false;
    session.user = null;
    return { ok: true };
  }
}
