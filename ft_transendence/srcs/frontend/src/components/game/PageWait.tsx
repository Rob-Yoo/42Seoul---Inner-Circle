function WaitPage (ctx: CanvasRenderingContext2D, CanvasWidth: number, CanvasHeight: number) {
	ctx.clearRect(0, 0, CanvasWidth, CanvasHeight);
	ctx.fillStyle = "BLACK";
	ctx.fillRect(0, 0, CanvasWidth, CanvasHeight);
	ctx.fillStyle = "WHITE";
	const fontSize = (CanvasWidth/15).toString();
	ctx.font = fontSize + "px serif";
	ctx.textAlign = "center";
	ctx.fillText("Waiting for...", CanvasWidth/2, CanvasHeight/2);
}

export default WaitPage;