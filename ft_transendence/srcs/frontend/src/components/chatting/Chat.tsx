import { useEffect, useState } from "react";
import { Card, Row, Image, OverlayTrigger, Popover } from "react-bootstrap";
import { Button } from "react-bootstrap";
import { useNavigate } from "react-router-dom";
import { api } from "../../axios/api";
import { myGameSocket, mySocket } from "../../common/MySocket";
import {
	BoolType,
	SocketInputDto,
	SocketOutputDto,
	SOCKET_EVENT,
	SOCKET_GAME_EVENT,
	UserData,
} from "../../common/types";

type ArgsType = {
	msg: SocketOutputDto;
	setReceivedMsg: React.Dispatch<
		React.SetStateAction<SocketOutputDto | undefined>
	>;
	setInform: React.Dispatch<React.SetStateAction<UserData | undefined>>;
};

export function Chat({ msg, setReceivedMsg, setInform }: ArgsType) {
	let [isFriend, setIsFriend]: BoolType = useState<boolean>(false);
	let [show, setShow]: BoolType = useState<boolean>(false);
	let [active, setActive]: BoolType = useState<boolean>(true);
	const [imageDataUrl, setImageDataUrl] = useState<string>();
	const navigate = useNavigate();

	const getUserData = async () => {
		if (msg.user?.avatarId) {
			await api
				.get(`/user/avatar/${msg.user?.avatarId}`, { responseType: "arraybuffer" })
				.then((response) => {
					const arrayBufferView = new Uint8Array(response.data);
					const blob = new Blob([arrayBufferView], { type: "image/jpeg" });
					const urlCreator = window.URL || window.webkitURL;
					const imageUrl = urlCreator.createObjectURL(blob);
					setImageDataUrl(imageUrl);
				})
				.catch((error) => console.error(error));
		}
		else {
			setImageDataUrl("./Anonymous.jpeg");
		}
	};
	useEffect(() => {
		if (msg.author !== 'server' && msg.author !== mySocket.name)
			getUserData();
	}, []);

	if (msg.author === "server") {
		return (
			<Row className="m-0 p-0 pb-1 h-auto text-left justify-content-center">
				<pre style={{ color: "red", whiteSpace: "pre-line" }}>
					{msg.message}
				</pre>
				<hr style={{ color: "red" }} />
			</Row>
		);
	} else {
		const checkFriend = async () => {
			const res = await api.get(`/user/friends`);
			if (res.data.friends.find((user: any) => user.nickname === msg.author))
				setIsFriend(true);
			else setIsFriend(false);
			show ? setShow(false) : setShow(true);
		};
		const beFriend = () => {
			let dto: SocketInputDto = {
				author: mySocket.name,
				target: msg.author,
			};
			mySocket.socket.emit(SOCKET_EVENT.BEFRIEND, dto, setReceivedMsg);
			setShow(false);
		};
		const delFriend = async () => {
			await api.delete(`/user/friends?nickname=${msg.author}`);
			setShow(false);
		};
		const showProfile = () => {
			msg.user && setInform(msg.user);
			setShow(false);
		};
		const joinGame = () => {
			navigate('/friendlyGame');
			myGameSocket.socket.emit(SOCKET_GAME_EVENT.GET_ROOM_NAME, msg.author,
				({success, payload}: {success: boolean, payload: string}) => {
					if (success) {
						myGameSocket.socket.emit(SOCKET_GAME_EVENT.JOIN, payload,
							({success, payload}: {success :boolean, payload :string}) => {
								setReceivedMsg({author:"server", message:payload})
						})
						mySocket.enteredGameRoom = true;
						setActive(false);
					}
					else {
						setReceivedMsg({author:'server', message:payload})
					}
				});
		};

		const weAreFriend = async () => {
			await api.post(`/user/friends?nickname=${msg.author}`);
			let dto: SocketInputDto = {
				author: mySocket.name,
				target: msg.author,
				message: "ok",
			};
			mySocket.socket.emit(SOCKET_EVENT.RESFRIEND, dto, setReceivedMsg);
			setActive(false);
		};
		const weAreNotFriend = () => {
			let dto: SocketInputDto = {
				author: mySocket.name,
				target: msg.author,
			};
			mySocket.socket.emit(SOCKET_EVENT.RESFRIEND, dto, setReceivedMsg);
			setActive(false);
		};
		return (
			<Row
				className={
					msg.author === mySocket.name
						? "m-0 p-0 pb-1 h-auto justify-content-end"
						: "m-0 p-0 pb-1 h-auto"
				}
			>
				{msg.author !== mySocket.name && (
					<>
						<OverlayTrigger
							key={"right"}
							placement={"right"}
							show={show}
							overlay={
								<Popover id={`popover-positioned-${"right"}`}>
									<Popover.Body>
										<Button
											variant="outline-dark"
											className="w-100 p-3 my-1"
											onClick={showProfile}
										>
											프로필 보기
										</Button>
										{isFriend ? (
											<Button
												variant="outline-dark"
												className="w-100 p-3 my-1"
												onClick={delFriend}
											>
												친구 삭제
											</Button>
										) : (
											<Button
												variant="outline-dark"
												className="w-100 p-3 my-1"
												onClick={beFriend}
											>
												친구 추가
											</Button>
										)}
									</Popover.Body>
								</Popover>
							}
						>
							<Image
								roundedCircle
								src={imageDataUrl ?? "/img/Anonymous.jpeg"}
								style={{ width: "50px", height: "50px" }}
								className="p-0 me-2"
								onClick={checkFriend}
							/>
						</OverlayTrigger>
					</>
				)}
				<Card
					className="d-flex h-auto w-75 p-0"
					bg={msg.type === SOCKET_EVENT.DM ? "danger" : "secondary"}
					text="white"
				>
					<Card.Header>
						{msg.type === SOCKET_EVENT.DM
							? msg.author === mySocket.name
								? `me -> ${msg.target}`
								: `${msg.author} -> me`
							: `${msg.author}`}
					</Card.Header>
					<Card.Text className="px-2"> {msg.message}</Card.Text>
					{msg.type === SOCKET_EVENT.INVITE && msg.author !== mySocket.name && (
						<Button
							variant="outline-dark"
							onClick={joinGame}
							disabled={mySocket.enteredGameRoom}
						>
							참여하기
						</Button>
					)}
					{msg.type === SOCKET_EVENT.BEFRIEND && (
						<>
							<Button
								variant="outline-dark"
								onClick={weAreFriend}
								disabled={!active}
							>
								수락
							</Button>
							<Button
								variant="outline-dark"
								onClick={weAreNotFriend}
								disabled={!active}
							>
								거절
							</Button>
						</>
					)}
				</Card>
			</Row>
		);
	}
}
