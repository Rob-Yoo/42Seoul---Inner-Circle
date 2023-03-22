import {
  changeAvatarOutput,
  CheckNickNameOutput,
  getMeOutput,
  getScoreByNickNameOutput,
  getUserByIdOutput,
  getUserByNickNameOutput,
  UpdateUserDto,
  UpdateUserOutput,
} from './dtos/user.dto';
import { UserService } from './user.service';
import {
  Body,
  Controller,
  Get,
  Patch,
  Query,
  UseGuards,
  Post,
  UseInterceptors,
  UploadedFile,
  ParseIntPipe,
  Param,
  Res,
  StreamableFile,
  Delete,
} from '@nestjs/common';
import { AuthGuard } from 'src/auth/auth.guard';
import { AuthUser } from 'src/auth/authUser.decorator';
import { ApiTags, ApiResponse } from '@nestjs/swagger';
import { FileInterceptor } from '@nestjs/platform-express';
import { Readable } from 'stream';
import { Response } from 'express';

export interface userSession {
  id: number;
  intra: string;
}

@ApiTags('user')
@Controller('user')
export class UserController {
  constructor(private readonly userService: UserService) {}

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'returns my info',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Get('/me')
  async getMe(@AuthUser() user: userSession): Promise<getMeOutput> {
    if (user) {
      return await this.userService.getMe(user.intra);
    }
    return { ok: false };
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'search user by nickname',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Get('/search')
  async getUserByNickName(
    @Query('nickname') nickname: string,
  ): Promise<getUserByNickNameOutput> {
    return await this.userService.getUserByNickName(nickname);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'check nickname exists or not',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Get('/check')
  async checkNickName(
    @Query('nickname') nickname: string,
  ): Promise<CheckNickNameOutput> {
    return await this.userService.checkNickName(nickname);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'update user info',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Patch('/update')
  async updateUser(
    @AuthUser() user: userSession,
    @Body() updateData: UpdateUserDto,
  ): Promise<UpdateUserOutput> {
    return await this.userService.updateUser(user.id, updateData);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'post avatar to user',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Post('avatar')
  @UseInterceptors(FileInterceptor('file'))
  async changeAvatar(
    @AuthUser() user: userSession,
    @UploadedFile() file: Express.Multer.File,
  ): Promise<changeAvatarOutput> {
    return this.userService.changeAvatar(
      user.id,
      file.buffer,
      file.originalname,
    );
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'get avatar by id',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Get('avatar/:id')
  async getAvatarById(
    @Param('id', ParseIntPipe) id: number,
    @Res({ passthrough: true }) response: Response,
  ) {
    const file = await this.userService.getAvatarById(id);
    const stream = Readable.from(file.data);

    response.set({
      'Content-Disposition': `inline; filename="${file.filename}"`,
      'Content-Type': 'image',
    });
    return new StreamableFile(stream);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'get freinds',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Get('/friends')
  async getFriends(@AuthUser() user: userSession) {
    return await this.userService.getFriends(user.id);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'add freind by nickname',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Post('/friends')
  async addFriends(
    @AuthUser() user: userSession,
    @Query('nickname') nickname: string,
  ) {
    return await this.userService.addFriends(user.id, nickname);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'delete freind by nickname',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Delete('/friends')
  async deleteFriends(
    @AuthUser() user: userSession,
    @Query('nickname') nickname: string,
  ) {
    return await this.userService.deleteFriends(user.id, nickname);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'get score by nickname',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Get('/score')
  async getScoreByNickName(
    @Query('nickname') nickname: string,
  ): Promise<getScoreByNickNameOutput> {
    return await this.userService.getScoreByNickName(nickname);
  }

  @UseGuards(AuthGuard)
  @ApiResponse({
    status: 200,
    description: 'get user by id',
  })
  @ApiResponse({ status: 403, description: 'Forbidden.' })
  @Get('/:id')
  async getUserById(
    @Param('id', ParseIntPipe) id: number,
  ): Promise<getUserByIdOutput> {
    return await this.userService.getUserById(id);
  }
}
