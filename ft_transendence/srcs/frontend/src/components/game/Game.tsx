import { useEffect, useState, useRef } from 'react';
import { useNavigate } from "react-router-dom";

import EndPage from './PageEnd';
import ReadyPage from './PageReady';
import WaitPage from './PageWait';
import Player from './PlayerBar';
import { myGameSocket, mySocket } from '../../common/MySocket';
import { BoolType, dataType, gameMod, playerType, SOCKET_GAME_EVENT } from '../../common/types';


type gameComponent = {
	mod: gameMod;
	isChangedGameData: boolean;
	setChangedGameData: React.Dispatch<React.SetStateAction<boolean>>;
	SetNeedclear: React.Dispatch<React.SetStateAction<boolean>>;
};

function Game({ mod, isChangedGameData, setChangedGameData, SetNeedclear}: gameComponent) {
	const canvasRef = useRef<HTMLCanvasElement>(null);
	let CanvasWidth = 1200;
	let CanvasHeight = 800;

	// const [canvas, setCanvas] = useState<HTMLCanvasElement | null>(null);
	// const [ctx, setCtx] = useState<CanvasRenderingContext2D | null>(null);
	const navigate = useNavigate();
	const [canvas, setCanvas] = useState<any>();
	const [ctx, setCtx] = useState<any>();
	const [player,setPlayer] :BoolType = useState<boolean>(true);

	const [startGame, setStartGame] :BoolType = useState<boolean>(false);
	const [isWatch, setIsWatch] :BoolType = useState<boolean>(false);
	const [isInfo, setIsInfo] :BoolType = useState<boolean>(false);
	const [playerInfo, setPlayerInfo] = useState<playerType>();

	let [data, setData] = useState<dataType>();

	useEffect(()=> {
		try {
			SetNeedclear(true);
			const canvas = canvasRef.current;
			if (canvas) {
				myGameSocket.socket.emit(SOCKET_GAME_EVENT.NICK, myGameSocket.name);
				canvas.height = CanvasHeight;
				canvas.width = CanvasWidth;
				setCanvas(canvas);
				setCtx(canvas.getContext("2d"));
			}
		}
		catch (error: any) {
			navigate('/');
		}
	}, []);

///////////////////// socket 관련 이벤트 /////////////////////////////////

	useEffect(() => {
		try {
			if (canvas && ctx) {
				// watch모드 대비 추가 iswatch일시 paddle 작동 막아둠
				if (mod === gameMod.watchGame) {
					myGameSocket.socket.emit('watching', (data: any) => {
						const PlayerInfo : playerType = {
							p1 : {
								intra: data.p1.intra,
								usual_full_name : data.p1.usual_full_name,
								nickname : data.p1.nickname,
								phone : data.p1.phone,
								verified : data.p1.verified,
								avatarId : data.p1.avatarId,
							},
							p2 : {
								intra: data.p2.intra,
								usual_full_name : data.p2.usual_full_name,
								nickname : data.p2.nickname,
								phone : data.p2.phone,
								verified : data.p2.verified,
								avatarId : data.p2.avatarId,
							}
						}
						setIsInfo(true);
						setPlayerInfo(PlayerInfo);
						setIsWatch(true);
					});
				}
				myGameSocket.socket.on('start-game', (res: any)=> {
					setPlayer(res);
					setStartGame(true);
				})
				// matching-success는 rank, 친선 경기시 상대방 들어왔을떄 이벤트 발생(ready 페이지)
				myGameSocket.socket.on('matching-success', (data: any) => {
					const PlayerInfo : playerType = {
						p1 : {
							intra: data.p1.intra,
							usual_full_name : data.p1.usual_full_name,
							nickname : data.p1.nickname,
							phone : data.p1.phone,
							verified : data.p1.verified,
							avatarId : data.p1.avatarId,
						},
						p2 : {
							intra: data.p2.intra,
							usual_full_name : data.p2.usual_full_name,
							nickname : data.p2.nickname,
							phone : data.p2.phone,
							verified : data.p2.verified,
							avatarId : data.p2.avatarId,
						}
					}
					mySocket.enteredGameRoom = true;
					setIsInfo(true);
					setPlayerInfo(PlayerInfo);
					ReadyPage(ctx, CanvasWidth, CanvasHeight);
					document.addEventListener('keydown', (e) => {
						if (e.code === 'KeyR') {
							myGameSocket.socket.emit('ready-rank');
						}
					});
			})
			// Sologame 특징: playerbar 컴포넌트 불러오지 않음
			if (mod === gameMod.soloGame) {
				ReadyPage(ctx, CanvasWidth, CanvasHeight);
				mySocket.enteredGameRoom = true;
				document.addEventListener('keydown', (e) => {
					if (e.code === 'KeyR') {
						myGameSocket.socket.emit(SOCKET_GAME_EVENT.SOLO_READY);
						setStartGame(true);
					}
				});
			}

			if (mod === gameMod.rankGame ||
				mod === gameMod.normalGame ||
				mod === gameMod.passwordGame) {
					WaitPage(ctx, CanvasWidth, CanvasHeight);
					if (mod === gameMod.rankGame)
						myGameSocket.socket.emit('matching');
				}
				// 매칭 성공 이벤트 받으면 레디 입력 받고 ready-rank 이벤트 보내야함
			}
			// 프론트에서 보여줄 데이터 받기 위한 소켓
			// 받을 때마다 USEEffect를 통해 render함수를 계속 실행
			myGameSocket.socket.on('update', (data: dataType) => {
				setData({
					leftPaddle : data.leftPaddle,
					rightPaddle : data.rightPaddle,
					ballX : data.ballX,
					ballY : data.ballY,
					leftScore : data.leftScore,
					rightScore : data.rightScore,
				})
			})
			myGameSocket.socket.on('end-game', (p1win: boolean) => {
				const ctx = canvas?.getContext("2d");
				if (ctx) {
					if (mod === gameMod.soloGame) {
						if (p1win)
							EndPage(ctx, CanvasWidth, CanvasHeight, "user");
						else
							EndPage(ctx, CanvasWidth, CanvasHeight, "com");
					}
					else {
						if (p1win)
							EndPage(ctx, CanvasWidth, CanvasHeight, "p1");
						else
							EndPage(ctx, CanvasWidth, CanvasHeight, "p2");
					}
					// 여기에 경기 결과 db에 업데이트 하는 코드 추가 (watch상태 아닐시에만)
					if (mod === gameMod.rankGame) {
						if (!isChangedGameData)
							setChangedGameData(true);
						// socket emit
					}
					if (mod === gameMod.normalGame || mod === gameMod.passwordGame) {
						if (!isChangedGameData)
							setChangedGameData(true);
						// socket emit
					}
					killSockets(myGameSocket.socket);
					mySocket.enteredGameRoom = false;
					myGameSocket.socket.emit('end-game');
				}
			})
		} catch (error: any) {
			navigate('/');
		}
		// eslint-disable-next-line react-hooks/exhaustive-deps
		}, [ctx])

		function killSockets(socket : any) {
			socket.off('end-game');
			socket.off('update');
			socket.off('start-game');
			socket.off('matching-success');
		}

		//////////////////////////paddle 관련 이벤트////////////////////////////

		let [paddleUp, setPaddleUp] = useState<boolean>(false);
		let [paddleDown, setPaddleDown] = useState<boolean>(false);

		document.addEventListener('keydown', (e) => {
			if (startGame) {
	var code = e.code;

			if (code === 'KeyS' && paddleDown === false) {
				setPaddleDown(true);
			}
			else if (code === 'KeyW' && paddleUp === false) {
				setPaddleUp(true);
			}
		}
	}, {once:true});

	document.addEventListener('keyup', (e) => {
		if (startGame) {
			var code = e.code;

			if (code === 'KeyS' && paddleDown === true) {
				setPaddleDown(false);
			}
			else if (code === 'KeyW' && paddleUp === true) {
				setPaddleUp(false);
			}
		}
	}, {once:true});

	useEffect(() => {
		// game시작 했을 때만 적용되게
		if (startGame && !isWatch) {
			if (paddleUp === true) {
				myGameSocket.socket.emit('PaddleUp', player);
			}
			if (paddleDown === true) {
				myGameSocket.socket.emit('PaddleDown', player);
			}
			if (paddleDown === false && paddleUp === false) {
				myGameSocket.socket.emit('PaddleStop', player);
			}
		}
	}, [paddleDown, paddleUp]);

//////////////////////////canvas draw Function//////////////////////////////////

	function drawRect(x: number, y:number, w:number, h:number, color:string) {
		if (ctx) {
			ctx.fillStyle = color;
			ctx.fillRect(x, y, w, h);
		}
	}

	function drawCircle(x:number, y:number, r:number, color:string) {
		if (ctx) {
			ctx.beginPath();
			ctx.fillStyle = color;
			ctx.arc(x, y, r, 0, Math.PI*2, false);
			ctx.fill();
			ctx.closePath();
		}
	}

	function drawNet() {
		for (let i = 0; i <= CanvasHeight; i += 15) {
			drawRect(CanvasWidth/2-2/2,i,2,10,"WHITE");
		}
	}

	function drawText(text:string, x:number, y:number, color:string) {
		if (ctx) {
			ctx.fillStyle = color;
			const fontSize = (CanvasWidth/8).toString();
			ctx.font = fontSize + "px serif";
			ctx.fillText(text, x, y);
		}
	}

/////////////////////////////// render Event /////////////////////////////////////

	useEffect(() => {
		if (canvas && ctx)
			if (data) {
				render(data);
			}
	}, [data])

	function render(data: dataType) {
		if (ctx) {
			ctx.clearRect(0, 0, CanvasWidth, CanvasHeight);
			drawRect(0, 0, CanvasWidth, CanvasHeight, "BLACK");
			drawText(data.leftScore.toString(),CanvasWidth/4,CanvasHeight/5,"WHITE");
			drawText(data.rightScore.toString(),3*CanvasWidth/4,CanvasHeight/5,"WHITE");
			drawNet();
			drawRect(5,data.leftPaddle,CanvasWidth/60,CanvasHeight/4,"WHITE");
			drawRect(CanvasWidth-(CanvasWidth/60+5),data.rightPaddle,CanvasWidth/60,CanvasHeight/4,"WHITE");
			drawCircle(data.ballX,data.ballY,CanvasWidth/60,"WHITE");
		}
	}

	const styleEl = document.createElement('style');
	styleEl.appendChild(document.createTextNode(styles));
	document.head.appendChild(styleEl);

	return (
		<div className='Game'>
			{isInfo && (
			<Player mod={mod} playerInfo={playerInfo} ></Player>
			)}
			<div className={isInfo ? 'canv2' : 'canv'}>
				<canvas
					className='border'
					ref={canvasRef}
					width={CanvasWidth}
					height={CanvasHeight}/>
			</div>
		</div>
	);
}

export default Game;

const styles = `
.Game {
	min-height: 100%;
	margin-top: 30px;
}

.canv {
	display: flex;
	width: 100%;
	margin: 0 auto;
	padding-top: 220px;
	align-items: center;
	justify-content:center;
	vertical-align: center;
}

.canv2 {
	display: flex;
	width: 100%;
	margin: 0 auto;
	padding-top: 100px;
	align-items: flex-start;
	justify-content:center;
}

`;
