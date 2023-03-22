import { DynamicModule, Global, Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import Avatar from 'src/user/entities/avatar.entity';
import { User } from 'src/user/entities/user.entity';
import { UserService } from 'src/user/user.service';
import { LoginController } from './login.controller';
import { loginModuleOptions } from './login.interfaces';
import { LoginService } from './login.service';

@Module({})
@Global()
export class LoginModule {
  static forRoot(options: loginModuleOptions): DynamicModule {
    return {
      module: LoginModule,
      imports: [TypeOrmModule.forFeature([User, Avatar])],
      exports: [LoginService],
      controllers: [LoginController],
      providers: [
        { provide: 'login_options', useValue: options },
        LoginService,
        UserService,
      ],
    };
  }
}
