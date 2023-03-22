import { BallDto } from './ball.dto';
import { PlayerDto } from './player.dto';
import { Namespace } from 'socket.io';
import { BaseOutput } from 'src/common/dtos/base.dto';

import {
  IsBoolean,
  IsDate,
  IsEnum,
  IsNumber,
  IsObject,
  IsOptional,
  IsString,
} from 'class-validator';

export enum gameMod {
  normalGame,
  passwordGame,
  soloGame,
  rankGame,
}

export class FrontData {
  @IsNumber()
  leftPaddle: number;
  @IsNumber()
  rightPaddle: number;
  @IsNumber()
  ballX: number;
  @IsNumber()
  ballY: number;
  @IsNumber()
  leftScore: number;
  @IsNumber()
  rightScore: number;
}

export class GameDto {
  @IsString()
  gameId: string;
  @IsString()
  roomName: string;
  @IsString()
  password: string;
  @IsObject()
  ball: BallDto;
  @IsObject()
  p1: PlayerDto;
  @IsObject()
  p2: PlayerDto;
  @IsEnum(gameMod)
  gameMod: gameMod;
  @IsObject()
  front: FrontData;
  @IsBoolean()
  p1Ready: boolean;
  @IsBoolean()
  p2Ready: boolean;
  nsp: Namespace;
  interval: NodeJS.Timer;
  @IsBoolean()
  start: boolean;
  @IsBoolean()
  end: boolean;
}

export class History2 {
  @IsNumber()
  id: number;
  @IsDate()
  createdAt: Date;
  @IsDate()
  updatedAt: Date;
  @IsString()
  winner: string;
  @IsString()
  loser: string;
  @IsEnum(gameMod)
  type: gameMod;
}

export class HistoryOutput extends BaseOutput {
  @IsOptional()
  history?: History2[];
}
