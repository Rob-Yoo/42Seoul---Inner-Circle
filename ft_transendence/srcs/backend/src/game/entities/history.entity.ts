import { BaseEntity } from 'src/common/entities/base.entity';
import { Column, Entity } from 'typeorm';
import { gameMod } from 'src/game/dtos/game.dto';
import { IsEnum, IsNumber, IsString } from 'class-validator';

@Entity('histories')
export class History extends BaseEntity {
  @IsString()
  @Column({ unique: true })
  gameId: string;

  @IsNumber()
  @Column()
  winner: number;

  @IsNumber()
  @Column()
  loser: number;

  @IsEnum(gameMod)
  @Column()
  type: gameMod;
}
