import { Module } from '@nestjs/common';
import { ChatGateway } from './chat.gateway';
import { ChatController } from './chat.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from 'src/user/entities/user.entity';
import { UserService } from 'src/user/user.service';
import Avatar from 'src/user/entities/avatar.entity';

@Module({
  imports: [TypeOrmModule.forFeature([User, Avatar])],
  providers: [ChatGateway, UserService],
  controllers: [ChatController],
  exports: [ChatGateway],
})
export class ChatModule {}
