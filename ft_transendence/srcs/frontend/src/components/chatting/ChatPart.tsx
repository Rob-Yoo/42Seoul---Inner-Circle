import { ChatMenuBar } from "./ChatMenuBar";
import { GameRooms } from "./GameRooms";
import {
	LEAVE_CHANNEL,
	ENTER_CHANNEL,
	SocketOutputDto,
	SHOW_OTHER,
	SHOW_CHATROOM,
	STARTMSG,
	SOCKET_EVENT,
	BoolType,
	UserData,
} from "../../common/types";
import { useEffect, useState } from "react";
import { ChatRoom } from "./ChatRoom";
import { mySocket } from "../../common/MySocket";
import { InputMsg } from "./InputMsg";
import { Channels } from "./Channels";

type ArgsType = {
	setInform: React.Dispatch<React.SetStateAction<UserData | undefined>>;
	setEnteredChannel: React.Dispatch<React.SetStateAction<boolean>>;
};

type MstList = [
	msgList: SocketOutputDto[],
	setMsgList: React.Dispatch<React.SetStateAction<SocketOutputDto[]>>
];
type ReceivedMsg = [
	receivedMsg: SocketOutputDto | undefined,
	setReceivedMsg: React.Dispatch<
		React.SetStateAction<SocketOutputDto | undefined>
	>
];

export default function ChatPart({ setInform, setEnteredChannel }: ArgsType) {
	let [msgList, setMsgList]: MstList = useState<SocketOutputDto[]>([STARTMSG]);
	let [receivedMsg, setReceivedMsg]: ReceivedMsg = useState<SocketOutputDto>();
	let [flag, setFlag]: BoolType = useState<boolean>(SHOW_CHATROOM);
	let [enterChannelFlag, setEnterChannelFlag]: BoolType =
		useState<boolean>(LEAVE_CHANNEL);

	const enterChannel = (dto: SocketOutputDto) => {
		if (dto.target === undefined) {
			mySocket.enteredChannelName = "";
			setEnteredChannel(false);
		}
		else {
			mySocket.enteredChannelName = dto.target;
			setEnteredChannel(true);
			setEnterChannelFlag(ENTER_CHANNEL);
		}
		setReceivedMsg(dto);
	};
	const exitChannel = () => {
		mySocket.socket.emit(
			SOCKET_EVENT.LEAVE,
			{ author: mySocket.name, target: mySocket.enteredChannelName },
			resetChannel
		);
	};
	const resetChannel = (dto: SocketOutputDto) => {
		mySocket.enteredChannelName = "";
		setEnteredChannel(false);
		setEnterChannelFlag(LEAVE_CHANNEL);
		setReceivedMsg(dto)
	}
	const setDMMsg = (dto: SocketOutputDto) => {
		dto.type = SOCKET_EVENT.DM;
		setReceivedMsg(dto);
	};
	const setInviteMsg = (dto: SocketOutputDto) => {
		dto.type = SOCKET_EVENT.INVITE;
		setReceivedMsg(dto);
	};
	const connectFriendMsg = (dto: SocketOutputDto) => {
		dto.type = SOCKET_EVENT.BEFRIEND;
		setReceivedMsg(dto);
	};
	const getOtherProfile = (dto: SocketOutputDto) => {
		if (dto.user) {
			dto.user && setInform(dto.user);
			setReceivedMsg(dto);
		}
	};

	useEffect(() => {
		mySocket.enteredChannelName === ""
			? setEnterChannelFlag(LEAVE_CHANNEL)
			: setEnterChannelFlag(ENTER_CHANNEL);
	}, [mySocket.enteredChannelName]);

	useEffect(() => {
		if (receivedMsg) {
			setMsgList([...msgList, receivedMsg]);
		}
	}, [receivedMsg]);

	useEffect(() => {
		mySocket.socket.on(SOCKET_EVENT.MSG, setReceivedMsg);
		mySocket.socket.on(SOCKET_EVENT.DM, setDMMsg);
		mySocket.socket.on(SOCKET_EVENT.INVITE, setInviteMsg);
		mySocket.socket.on(SOCKET_EVENT.NOTICE, setReceivedMsg);
		mySocket.socket.on(SOCKET_EVENT.BEFRIEND, connectFriendMsg);
		mySocket.socket.on(SOCKET_EVENT.LEAVE, resetChannel);
		return () => {
			mySocket.socket.off(SOCKET_EVENT.MSG, setReceivedMsg);
			mySocket.socket.off(SOCKET_EVENT.DM, setDMMsg);
			mySocket.socket.off(SOCKET_EVENT.INVITE, setInviteMsg);
			mySocket.socket.off(SOCKET_EVENT.NOTICE, setReceivedMsg);
			mySocket.socket.off(SOCKET_EVENT.BEFRIEND, connectFriendMsg);
		};
	}, []);

	return (
		<>
			<ChatMenuBar
				flag={flag}
				setFlag={setFlag}
				enterChannelFlag={enterChannelFlag}
				exitChannel={exitChannel}
			/>
			{flag === SHOW_OTHER ? (
				enterChannelFlag === ENTER_CHANNEL ? (
					<GameRooms setReceivedMsg={setReceivedMsg}/>
				) : (
					<Channels enterChannel={enterChannel} />
				)
			) : (
				<ChatRoom
					msgList={msgList}
					setReceivedMsg={setReceivedMsg}
					setInform={setInform}
				/>
			)}
			{flag === SHOW_CHATROOM && (
				<InputMsg
					setReceivedMsg={setReceivedMsg}
					enterChannel={enterChannel}
					setDMMsg={setDMMsg}
					setInviteMsg={setInviteMsg}
					getOtherProfile={getOtherProfile}
				/>
			)}
		</>
	);
}
