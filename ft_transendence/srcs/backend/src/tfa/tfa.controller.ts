import { Controller, Post, Query, UseGuards } from '@nestjs/common';
import { ApiResponse, ApiTags } from '@nestjs/swagger';
import { AuthGuard } from 'src/auth/auth.guard';
import { AuthUser } from 'src/auth/authUser.decorator';
import { userSession } from 'src/user/user.controller';
import { SendSMSOutput, VerifyUserOutput } from './dtos/tfa.dto';
import { TfaService } from './tfa.service';

@ApiTags('tfa')
@Controller('tfa')
export class TfaController {
  constructor(private readonly tfaService: TfaService) {}

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'send SMS to verify phone number',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Post('send')
  async sendSMS(
    @AuthUser() user: userSession,
    @Query('phone') phone: string,
  ): Promise<SendSMSOutput> {
    return await this.tfaService.sendSMS(user.id, phone);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'verify user',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Post('/verify')
  async verifyUser(
    @AuthUser() user: userSession,
    @Query('code') code: string,
  ): Promise<VerifyUserOutput> {
    return await this.tfaService.verifyUser(user.id, code);
  }
}
