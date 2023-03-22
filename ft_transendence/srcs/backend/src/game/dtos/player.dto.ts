import { IsBoolean, IsNumber, IsString } from 'class-validator';
import { Socket } from 'socket.io'

export class PlayerDto {
  @IsString()
  name: string;
  @IsNumber()
  padleX: number;
  @IsNumber()
  padleY: number;
  @IsNumber()
  padleW: number;
  @IsNumber()
  padleH: number;
  @IsBoolean()
  padleUp: boolean;
  @IsBoolean()
  padleDown: boolean;
  @IsNumber()
  speed: number;
  @IsNumber()
  score: number;
  socket: Socket;
}
