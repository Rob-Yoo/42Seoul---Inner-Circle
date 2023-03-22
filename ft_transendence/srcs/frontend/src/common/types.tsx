import React from "react";

//////////////////////////// CHAT TYPE /////////////////////////////////////
export interface UserData {
	intra: string,
	usual_full_name: string,
	nickname: string,
	verified: boolean,
	phone: string,
    avatarId: number,
    // history: any,
}

export interface SocketInputDto {
    author?: string; // nickname
    target?: string; // nickname or channel name
    message?: string;
    password?: string;
}

export interface SocketOutputDto {
    author?: string; // nickname
    target?: string; // nickname or channel name
    message?: string;
    type?: string;
    user?: UserData;
}

export interface ChannelType {
    name: string;
    password: boolean;
}

export interface GameRoomType {
    roomName: string,
	password: boolean,
}

export type BoolType = [
	boolean,
	React.Dispatch<React.SetStateAction<boolean>>
];

export type InputEvent = React.FormEvent<HTMLFormElement>;

export const SOCKET_EVENT = {
    MSG: "channel-msg",
    DM: "direct-msg",
    GET_CHANNEL: "channel-list",
    GET_GAMEROOM: "gameroom-list",
    JOIN: "join-channel",
    EMPOWER: "authorize",
    LEAVE: "leave-channel",
    SET_PW: "password",
    HIDE: "private",
    SHOW: "deprivate",
    BAN: "channel-ban",
    MUTE: "channel-mute",
    UNMUTE: "channel-unmute",
    BLOCK: "direct-mute",
    UNBLOCK: "direct-unmute",
    INVITE: "invite",
    BEFRIEND: "be-friend",
    RESFRIEND: "res-friend",
    NOTICE: "notice",
    PROFILE: "get-profile",
}

export const SHOW_CHATROOM :boolean = true;
export const SHOW_OTHER :boolean = false;

export const ENTER_CHANNEL :boolean = true;
export const LEAVE_CHANNEL :boolean = false;

const CHANNEL :string = "채널 생성\n/CHANNEL <채널 이름>"
const DM :string = "다이렉트 메세지\n/DM <유저 이름> <보낼 메세지>";
const INVITE :string = "게임 초대\n/INVITE <유저 이름/닉네임>";
const PROFILE :string = "유저 프로필\n/PROFILE <유저 이름/닉네임>";
const BLOCK :string = "개인유저 채팅 숨김\n/BLOCK <유저 이름/닉네임>"
const UNBLOCK :string = "개인유저 채팅 보임\n/UNBLOCK <유저 이름/닉네임>"

const ROOMSTATE :string = "채널 상태 변경\n/ROOMSTATE (-h[private]) (-p[protected] <비밀번호>)"
const EMPOWER :string = "ADMIN 권한 주기\n/EMPOWER <유저 이름/닉네임>"
const BAN :string = "유저 강퇴\n/BAN <유저 이름/닉네임>";
const MUTE :string = "채널유저 채팅 숨김\n/MUTE <유저 이름/닉네임>";
const UNMUTE :string = "채널유저 채팅 보임\n/UNMUTE <유저 이름/닉네임>";

export const WRONGINPUT :string = "잘못된 입력입니다.";
export const HELP :string = `-------------------------- 명령어 목록 ---------------------------
꺽쇠기호('<', '>')속 지정된 문자열에 White Space는 문자가 아닙니다.

${CHANNEL}

${DM}

${INVITE}

${PROFILE}

${BLOCK}

${UNBLOCK}

---------------------- CHANNEL OWNER 명령어 ---------------------

${ROOMSTATE}

${EMPOWER}

${BAN}

${MUTE}

${UNMUTE}

---------------------- CHANNEL ADMIN 명령어 ---------------------

${BAN}

${MUTE}

${UNMUTE}
`;

export const STARTMSG : SocketOutputDto = {
    author :"server",
    message :"반갑습니다!\n사용법 확인은 \"/HELP\"를 입력해주세요.",
}

//////////////////////////// GAME TYPE ////////////////////////////////////

export interface GameData {
	timestamp: string;
	nickname: string;
	isRank: boolean;
	isWin: boolean;
}

export enum gameMod{
	normalGame,
	passwordGame,
	soloGame,
	rankGame,
	watchGame,
}

export const SOCKET_GAME_EVENT = {
    MATCH: "matching",
    MATCH_SUCCESS: "matching-success",
    START: "start-game",
    END: "end-game",
    RANK_READY: "ready-rank",
    SOLO_READY: "ready-solo",
    UPDATE: "update",
	NICK: "nickname",
    JOIN: "join-room",
    LIST: "room-list",
    WATCH: "watch-room",
    GET_ROOM_NAME: "find-room",
}

type userType = {
	x : number,
	y : number,
	width : number,
	height : number,
	speed: number,
	color : string,
}

type netType = {
	x : number,
	y :	number,
	width : number,
	height : number,
	color : string,
}

type ballType = {
	x : number,
	y : number,
	radius : number,
	velocityX : number,
	velocityY : number,
	speed : number,
	color : string,
}

type dataType = {
  leftPaddle : number,
  rightPaddle : number,
  ballX : number,
  ballY : number,
  leftScore: number,
  rightScore: number,
}

type playerType = {
    p1 : UserData,
    p2 : UserData
}

export type { userType, netType, ballType, dataType, playerType }
