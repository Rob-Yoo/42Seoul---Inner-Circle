import { useRef } from "react";
import { Button, Container, Form, InputGroup, Row } from "react-bootstrap";
import {
	HELP,
	WRONGINPUT,
	SocketInputDto,
	SocketOutputDto,
	SOCKET_EVENT,
} from "../../common/types";
import { mySocket } from "../../common/MySocket";

type ArgsType = {
	setReceivedMsg: React.Dispatch<
		React.SetStateAction<SocketOutputDto | undefined>
	>;
	enterChannel: (dto: SocketOutputDto) => void;
	setDMMsg: (dto: SocketOutputDto) => void;
	setInviteMsg: (dto: SocketOutputDto) => void;
    getOtherProfile: (dto: SocketOutputDto) => void;
};

export function InputMsg({
	setReceivedMsg,
	enterChannel,
	setDMMsg,
	setInviteMsg,
	getOtherProfile,
}: ArgsType) {
	const chatInputRef = useRef<HTMLInputElement>(null);

	const submitHandler = (event: React.FormEvent<HTMLElement>) => {
		event.preventDefault();
		if (chatInputRef.current!.value !== "") {
			let text: string | undefined = chatInputRef.current!.value;
			let words: string[] = chatInputRef.current!.value.split(" ");
			const enteredMSG: SocketInputDto = {
				author: mySocket.name,
				target: mySocket.enteredChannelName,
				message: text,
				password: "",
			};
			switch (words[0]) {
				case "/HELP":
					text = HELP;
					words.length !== 1
						? setReceivedMsg({
								author: "server",
								message: `${text} :${WRONGINPUT}`,
						  })
						: setReceivedMsg({ author: "server", message: text });
					break;
				case "/CHANNEL":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					enteredMSG.target = words[1];
					mySocket.socket.emit(SOCKET_EVENT.JOIN, enteredMSG, enterChannel);
					break;
				case "/DM":
					if (words.length < 3) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					text = chatInputRef.current!.value.slice(
						words[0].length + words[1].length + 2
					);
					enteredMSG.target = words[1];
					enteredMSG.message = text;
					mySocket.socket.emit(SOCKET_EVENT.DM, enteredMSG, setDMMsg);
					break;
				case "/INVITE":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					else if (!mySocket.enteredGameRoom) {
						setReceivedMsg({
							author: "server",
							message: `${text} : Be out of the room`,
						});
						break;
					}
					else {
						enteredMSG.target = words[1];
					}
					mySocket.socket.emit(SOCKET_EVENT.INVITE, enteredMSG, setReceivedMsg);
					break;
				case "/PROFILE":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					} else {
						enteredMSG.target = words[1];
					}
					mySocket.socket.emit(SOCKET_EVENT.PROFILE, enteredMSG, getOtherProfile);
					break;
				case "/BLOCK":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					enteredMSG.target = words[1];
					mySocket.socket.emit(SOCKET_EVENT.BLOCK, enteredMSG, setReceivedMsg);
					break;
				case "/UNBLOCK":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					enteredMSG.target = words[1];
					mySocket.socket.emit(
						SOCKET_EVENT.UNBLOCK,
						enteredMSG,
						setReceivedMsg
					);
					break;
				case "/ROOMSTATE":
					let hide: boolean = false;
					let idx: number = 1;

					for (; idx < words.length; ++idx) {
						if (words[idx][0] === "-" && words[idx].length === 2) {
							if (
								words[idx][1] === "p" &&
								enteredMSG.password === "" &&
								idx + 1 !== words.length
							) {
								enteredMSG.password = words[++idx];
							} else if (words[idx][1] === "h" && hide === false) {
								hide = true;
							} else {
								break;
							}
						} else {
							break;
						}
					}
					if (idx !== words.length) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					mySocket.socket.emit(SOCKET_EVENT.SET_PW, enteredMSG, setReceivedMsg);
					hide === true
						? mySocket.socket.emit(
								SOCKET_EVENT.HIDE,
								enteredMSG,
								setReceivedMsg
						  )
						: mySocket.socket.emit(
								SOCKET_EVENT.SHOW,
								enteredMSG,
								setReceivedMsg
						  );
					break;
				case "/EMPOWER":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					enteredMSG.target = words[1];
					mySocket.socket.emit(
						SOCKET_EVENT.EMPOWER,
						enteredMSG,
						setReceivedMsg
					);
					break;
				case "/BAN":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					enteredMSG.target = words[1];
					mySocket.socket.emit(SOCKET_EVENT.BAN, enteredMSG, setReceivedMsg);
					break;
				case "/MUTE":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					enteredMSG.target = words[1];
					mySocket.socket.emit(SOCKET_EVENT.MUTE, enteredMSG, setReceivedMsg);
					break;
				case "/UNMUTE":
					if (words.length !== 2) {
						setReceivedMsg({
							author: "server",
							message: `${text} :${WRONGINPUT}`,
						});
						break;
					}
					enteredMSG.target = words[1];
					mySocket.socket.emit(SOCKET_EVENT.UNMUTE, enteredMSG, setReceivedMsg);
					break;
				default:
					mySocket.socket.emit(SOCKET_EVENT.MSG, enteredMSG, setReceivedMsg);
					break;
			}
			chatInputRef.current!.value = "";
		}
	};

	return (
		<Container className="p-0 m-0 pt-3" style={{ height: "6vmin" }}>
			<Row>
				<hr style={{ color: "white" }} />
			</Row>
			<Row>
				<form onSubmit={submitHandler}>
					<InputGroup>
						<Form.Control
							placeholder="메세지 보내기"
							aria-label="With textarea"
							aria-describedby="basic-addon2"
							ref={chatInputRef}
						/>
						<Button variant="outline-light" id="button-addon2" type="submit">
							보내기
						</Button>
					</InputGroup>
				</form>
			</Row>
		</Container>
	);
}
