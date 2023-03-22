import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Socket, Namespace } from 'socket.io';
import { UserService } from 'src/user/user.service';
import { Repository } from 'typeorm';
import type { GameDto, History2, HistoryOutput } from './dtos/game.dto';
import { gameMod } from './dtos/game.dto';
import { PlayerDto } from './dtos/player.dto';
import { History } from './entities/history.entity';
import * as bcrypt from 'bcrypt';
import { v4 as uuidv4 } from 'uuid';

// Cluster
const CanvasWidth = 1200;
const CanvasHeight = 800;
// // Laptop
// const CanvasWidth = 600;
// const CanvasHeight = 400;
const VictoryScore = 3;

@Injectable()
export class GameService {
  constructor(
    @InjectRepository(History) private readonly histories: Repository<History>,
    private readonly userService: UserService,
  ) {}

  async createDummyHistory(winner: string, type: gameMod) {
    try {
      const { user: user1 } = await this.userService.getUserByNickName(winner);
      const history: History = await this.histories.save(
        this.histories.create({ winner: user1.id, loser: user1.id, type }),
      );
      const h: History[] = [];
      h.push(history);
      return { ok: true, history: h };
    } catch (error) {
      return { ok: false, error: 'createHistory Error' };
    }
  }

  async createHistory(
    gameId: string,
    winner: string,
    loser: string,
    type: gameMod,
  ): Promise<HistoryOutput> {
    try {
      const { user: user1 } = await this.userService.getUserByNickName(winner);
      const { user: user2 } = await this.userService.getUserByNickName(loser);

      await this.histories.save(
        this.histories.create({
          gameId,
          winner: user1.id,
          loser: user2.id,
          type,
        }),
      );
      return { ok: true };
    } catch (error) {
      return { ok: false, error: 'createHistory Error' };
    }
  }

  async getHistory(nickname: string): Promise<HistoryOutput> {
    try {
      const { user } = await this.userService.getUserByNickName(nickname);
      const winner = user.id;
      const loser = user.id;
      const history = await this.histories.find({
        where: [{ winner }, { loser }],
      });
      const promises = history.map(async (item) => {
        const { winner, loser } = item;
        const {
          user: { nickname: winnerNickname },
        } = await this.userService.getUserById(winner);
        const {
          user: { nickname: loserNickname },
        } = await this.userService.getUserById(loser);
        return { ...item, winner: winnerNickname, loser: loserNickname };
      });
      const results: History2[] = await Promise.all(promises);
      if (history) return { ok: true, history: results };
      return { ok: false, error: 'History not Found' };
    } catch (error) {
      return { ok: false, error: 'getWinHistory Error' };
    }
  }

  async deleteHistory(id: number) {
    await this.histories.delete(id);
  }

  init_test(p1: Socket, roomName: string, GameMod: gameMod): GameDto {
    const params: GameDto = <GameDto>{
      roomName: roomName,
      ball: {
        x: CanvasWidth / 2,
        y: CanvasHeight / 2,
        radius: CanvasWidth / 60,
        speed: CanvasWidth / 100,
        velocityX: CanvasWidth / 120,
        velocityY: CanvasWidth / 120,
      },
      p1: {
        name: 'user',
        padleX: 5,
        padleY: (CanvasHeight - CanvasHeight / 4) / 2,
        padleW: CanvasWidth / 60,
        padleH: CanvasHeight / 4,
        score: 0,
        padleUp: false,
        padleDown: false,
        speed: CanvasWidth / 80,
        socket: p1,
      },
      p2: {
        name: 'com',
        padleX: CanvasWidth - (CanvasWidth / 60 + 5),
        padleY: (CanvasHeight - CanvasHeight / 4) / 2,
        padleW: CanvasWidth / 60,
        padleH: CanvasHeight / 4,
        score: 0,
        padleUp: false,
        padleDown: false,
        speed: CanvasWidth / 80,
      },
      gameMod: GameMod,
      front: {
        leftPaddle: (CanvasHeight - CanvasHeight / 4) / 2,
        rightPaddle: (CanvasHeight - CanvasHeight / 4) / 2,
        ballX: CanvasWidth / 2,
        ballY: CanvasHeight / 2,
      },
      start: false,
      end: false,
    };
    return params;
  }

  init_game(
    p1: Socket,
    p1NickName: string,
    roomName: string,
    GameMod: gameMod,
    nsp: Namespace,
  ): GameDto {
    const params: GameDto = <GameDto>{
      roomName: roomName,
      gameId: uuidv4(),
      password: undefined,
      ball: {
        x: CanvasWidth / 2,
        y: CanvasHeight / 2,
        radius: CanvasWidth / 60,
        speed: CanvasWidth / 100,
        velocityX: CanvasWidth / 120,
        velocityY: CanvasWidth / 120,
      },
      p1: {
        name: p1NickName, // 에러나서 임시로 고침
        padleX: 5,
        padleY: (CanvasHeight - CanvasHeight / 4) / 2,
        padleW: CanvasWidth / 60,
        padleH: CanvasHeight / 4,
        score: 0,
        padleUp: false,
        padleDown: false,
        speed: CanvasHeight / 80,
        socket: p1,
      },
      p2: {
        name: undefined, // 에러나서 임시로 고침
        padleX: CanvasWidth - (CanvasWidth / 60 + 5),
        padleY: (CanvasHeight - CanvasHeight / 4) / 2,
        padleW: CanvasWidth / 60,
        padleH: CanvasHeight / 4,
        score: 0,
        padleUp: false,
        padleDown: false,
        speed: CanvasHeight / 80,
        socket: undefined,
      },
      gameMod: GameMod,
      front: {
        leftPaddle: (CanvasHeight - CanvasHeight / 4) / 2,
        rightPaddle: (CanvasHeight - CanvasHeight / 4) / 2,
        ballX: CanvasWidth / 2,
        ballY: CanvasHeight / 2,
      },
      p1Ready: false,
      p2Ready: false,
      nsp: nsp,
      interval: undefined,
      start: false,
      end: false,
    };
    return params;
  }

  private resetBall(GameDto: GameDto) {
    GameDto.ball.x = CanvasWidth / 2;
    GameDto.ball.y = CanvasHeight / 2;
    GameDto.ball.speed = CanvasWidth / 100;
    if (GameDto.ball.velocityX > 0)
      GameDto.ball.velocityX = -(CanvasWidth / 100);
    else GameDto.ball.velocityX = CanvasWidth / 100;
    GameDto.ball.velocityY = CanvasWidth / 100;
  }

  private collision(GameDto: GameDto, player: PlayerDto): boolean {
    const player_top = player.padleY;
    const player_bottom = player.padleY + player.padleH;
    const player_left = player.padleX;
    const player_right = player.padleX + player.padleW;

    const ball_top = GameDto.ball.y - GameDto.ball.radius;
    const ball_bottom = GameDto.ball.y + GameDto.ball.radius;
    const ball_left = GameDto.ball.x - GameDto.ball.radius;
    const ball_right = GameDto.ball.x + GameDto.ball.radius;
    return (
      ball_right > player_left &&
      ball_top < player_bottom &&
      ball_left < player_right &&
      ball_bottom > player_top
    );
  }

  private async update_v2(Game: GameDto) {
    // 공이 양쪽 벽에 닿아서 점수 발생했는지 체크
    if (Game.ball.x + Game.ball.radius < 0) {
      Game.p2.score++;
      this.resetBall(Game);
    } else if (Game.ball.x - Game.ball.radius > CanvasWidth) {
      Game.p1.score++;
      this.resetBall(Game);
    }
    // 게임이 끝났는지 체크
    if (Game.p1.score >= VictoryScore) {
      await this.finishGame(Game, true);
      return;
    } else if (Game.p2.score >= VictoryScore) {
      await this.finishGame(Game, false);
      return;
    }
    // 패들 움직임 계산
    this.paddleCalculate(Game);
    // 공 위치 계산
    Game.ball.x += Game.ball.velocityX;
    Game.ball.y += Game.ball.velocityY;
    // 공의 y좌표가 화면을 벗어나면 수정
    if (Game.ball.y < 0) Game.ball.y = 0;
    else if (Game.ball.y > CanvasHeight) Game.ball.y = CanvasHeight;
    // soloMod 컴퓨터 패들 조종
    if (Game.gameMod == gameMod.soloGame) {
      Game.p2.padleY +=
        (Game.ball.y - (Game.p2.padleY + Game.p2.padleH / 2)) * 0.1;
      if (Game.p2.padleY + Game.p2.padleH > CanvasHeight)
        Game.p2.padleY = CanvasHeight - Game.p2.padleH;
      else if (Game.p2.padleY < 0) Game.p2.padleY = 0;
    }
    // 공에 가까운 플레이어 선택
    const player = Game.ball.x < CanvasWidth / 2 ? Game.p1 : Game.p2;
    // 공이 천장과 바닥에 닿았으면 y축 방향을 반전
    if (
      Game.ball.y - Game.ball.radius <= 0 ||
      Game.ball.y + Game.ball.radius >= CanvasHeight
    )
      Game.ball.velocityY = -Game.ball.velocityY;
    // 공이 플레이어의 패들에 충돌시
    if (this.collision(Game, player)) {
      let collidePoint = Game.ball.y - (player.padleY + player.padleH / 2);
      collidePoint = collidePoint / (player.padleH / 2);
      const angleRad = (Math.PI / 4) * collidePoint;
      const direction =
        Game.ball.x + Game.ball.radius < CanvasWidth / 2 ? 1 : -1;
      Game.ball.velocityX = direction * Game.ball.speed * Math.cos(angleRad);
      Game.ball.velocityY = Game.ball.speed * Math.sin(angleRad);
      Game.ball.speed += 1;
    }
    // 프론트로 보낼 데이터 저장
    Game.front.leftPaddle = Game.p1.padleY;
    Game.front.rightPaddle = Game.p2.padleY;
    Game.front.ballX = Game.ball.x;
    Game.front.ballY = Game.ball.y;
    Game.front.leftScore = Game.p1.score;
    Game.front.rightScore = Game.p2.score;
    // render 호출하는 socket 추가
    if (Game.gameMod == gameMod.soloGame)
      Game.p1.socket.emit('update', Game.front);
    else Game.nsp.in(Game.roomName).emit('update', Game.front);
  }

  paddleUp(client: Socket, Game: GameDto) {
    if (client.id === Game.p1.socket.id) Game.p1.padleUp = true;
    else Game.p2.padleUp = true;
  }

  paddleDown(client: Socket, Game: GameDto) {
    if (client.id === Game.p1.socket.id) Game.p1.padleDown = true;
    else Game.p2.padleDown = true;
  }

  paddleStop(client: Socket, Game: GameDto) {
    if (client.id === Game.p1.socket.id) {
      Game.p1.padleUp = false;
      Game.p1.padleDown = false;
    } else {
      Game.p2.padleUp = false;
      Game.p2.padleDown = false;
    }
  }

  private paddleCalculate(Game: GameDto) {
    if (Game.p1.padleUp === true) {
      if (Game.p1.padleY > 0) {
        Game.p1.padleY -= Game.p1.speed;
      }
    }
    if (Game.p1.padleDown === true) {
      if (Game.p1.padleY < CanvasHeight - Game.p1.padleH) {
        Game.p1.padleY += Game.p1.speed;
      }
    }
    if (Game.p2.padleUp === true) {
      if (Game.p2.padleY > 0) {
        Game.p2.padleY -= Game.p2.speed;
      }
    }
    if (Game.p2.padleDown === true) {
      if (Game.p2.padleY < CanvasHeight - Game.p2.padleH) {
        Game.p2.padleY += Game.p2.speed;
      }
    }
  }

  async hashPassword(password: string): Promise<string> {
    if (!password) return undefined;
    const saltRounds = 10;
    const salt = await bcrypt.genSalt(saltRounds);
    const hashedPassword = await bcrypt.hash(password, salt);
    return hashedPassword;
  }

  async verifyPassword(
    password: string,
    hashedPassword: string,
  ): Promise<boolean> {
    if (!password && !hashedPassword) return true;
    const isMatch = await bcrypt.compare(password, hashedPassword);
    return isMatch;
  }

  gameLoop(Game: GameDto) {
    Game.interval = setInterval(() => {
      this.update_v2(Game);
    }, 1000 / 45);
  }

  async finishGame(Game: GameDto, p1_win: boolean) {
    if (Game.end) return;
    if (p1_win) {
      if (Game.gameMod != gameMod.soloGame) {
        const res = await this.createHistory(
          Game.gameId,
          Game.p1.name,
          Game.p2.name,
          Game.gameMod,
        );
        if (res.ok) {
          await this.userService.winGame(Game.p1.name, Game.gameMod);
          await this.userService.loseGame(Game.p2.name, Game.gameMod);
        }
        Game.nsp.in(Game.roomName).emit('end-game', true);
      } else {
        Game.p1.socket.emit('end-game', true);
      }
    } else {
      if (Game.gameMod != gameMod.soloGame) {
        const res = await this.createHistory(
          Game.gameId,
          Game.p2.name,
          Game.p1.name,
          Game.gameMod,
        );
        if (res.ok) {
          await this.userService.winGame(Game.p2.name, Game.gameMod);
          await this.userService.loseGame(Game.p1.name, Game.gameMod);
        }
        Game.nsp.in(Game.roomName).emit('end-game', false);
      } else Game.p1.socket.emit('end-game', false);
    }
    clearInterval(Game.interval);
    Game.end = true;
  }
}
