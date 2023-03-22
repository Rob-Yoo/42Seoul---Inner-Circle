import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { UserModule } from './user/user.module';
import { AuthModule } from './auth/auth.module';
import { LoginModule } from './login/login.module';
import { TfaModule } from './tfa/tfa.module';
import { ChatModule } from './chat/chat.module';
import { GameModule } from './game/game.module';
import { ValidationPipe } from '@nestjs/common';
import { APP_PIPE } from '@nestjs/core';

@Module({
  imports: [
    TypeOrmModule.forRoot({
      type: 'postgres',
      host: process.env.POSTGRES_HOST,
      port: parseInt(process.env.POSTGRES_PORT),
      username: process.env.POSTGRES_USER,
      password: process.env.POSTGRES_PASSWORD,
      database: process.env.POSTGRES_DB,
      synchronize: true,
      logging: false,
      entities: ['dist/**/*.entity.{ts,js}'],
    }),
    UserModule,
    AuthModule,
    LoginModule.forRoot({
      baseUrl: process.env.NESTJS_42API_BASE,
      uid: process.env.NESTJS_UID,
      secret: process.env.NESTJS_SECRET,
      redirect: `http://${process.env.NESTJS_HOST}:${process.env.NESTJS_PORT}/login/redirect`,
    }),
    TfaModule.forRoot({
      apiKey: process.env.NESTJS_SOLAPI_API,
      secretKey: process.env.NESTJS_SOLAPI_SECRET,
      sender: process.env.NESTJS_SOLAPI_SENDER,
    }),
    ChatModule,
    GameModule,
  ],
  controllers: [AppController],
  providers: [
    AppService,
    {
      provide: APP_PIPE,
      useClass: ValidationPipe,
    },
  ],
})
export class AppModule {}
