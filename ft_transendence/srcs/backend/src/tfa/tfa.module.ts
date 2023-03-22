import { UserService } from 'src/user/user.service';
import { User } from 'src/user/entities/user.entity';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Module, DynamicModule } from '@nestjs/common';
import { TfaController } from './tfa.controller';
import { TfaService } from './tfa.service';
import { tfaModuleOptions } from './tfa.interfaces';
import Avatar from 'src/user/entities/avatar.entity';

@Module({})
export class TfaModule {
  static forRoot(options: tfaModuleOptions): DynamicModule {
    return {
      module: TfaModule,
      imports: [TypeOrmModule.forFeature([User, Avatar])],
      controllers: [TfaController],
      providers: [
        { provide: 'tfa_options', useValue: options },
        TfaService,
        UserService,
      ],
    };
  }
}
