import { playerType } from "../../common/types";

function EndPage (ctx: CanvasRenderingContext2D, CanvasWidth: number, CanvasHeight: number, name: string | undefined) {
	ctx.clearRect(0, 0, CanvasWidth, CanvasHeight);
	ctx.fillStyle = "BLACK";
	ctx.fillRect(0, 0, CanvasWidth, CanvasHeight);
	ctx.fillStyle = "WHITE";
	const fontSize = (CanvasWidth/15).toString();
	ctx.font = fontSize + "px serif";
	ctx.textAlign = "center";
	const res = name + " win";
	ctx.fillText(res, CanvasWidth/2, CanvasHeight/2);
}

export default EndPage;