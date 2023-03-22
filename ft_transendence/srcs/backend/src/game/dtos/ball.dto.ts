import { IsNumber } from "class-validator";

export class BallDto {
  @IsNumber()
  x: number;
  @IsNumber()
  y: number;
  @IsNumber()
  radius: number;
  @IsNumber()
  speed: number;
  @IsNumber()
  velocityX: number;
  @IsNumber()
  velocityY: number;
}
