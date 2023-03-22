import { Controller, Get, Query, UseGuards } from '@nestjs/common';
import { AuthGuard } from 'src/auth/auth.guard';
import { ApiTags, ApiResponse } from '@nestjs/swagger';
import { GameService } from './game.service';

@ApiTags('game')
@Controller('game')
export class GameController {
  constructor(private gameService: GameService) {}

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'search history by nickname',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Get('/history')
  async getHistory(@Query('nickname') nickname: string) {
    return await this.gameService.getHistory(nickname);
  }
}
