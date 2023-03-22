import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { GameController } from './game.controller';
import { GamesGateway } from './game.gateway';
import { GameService } from './game.service';
import { User } from 'src/user/entities/user.entity';
import { UserService } from 'src/user/user.service';
import Avatar from 'src/user/entities/avatar.entity';
import { History } from './entities/history.entity';

@Module({
  imports: [TypeOrmModule.forFeature([User, Avatar, History])],
  providers: [GameService, GamesGateway, UserService],
  controllers: [GameController],
  exports: [GameService, GamesGateway],
})
export class GameModule {}
