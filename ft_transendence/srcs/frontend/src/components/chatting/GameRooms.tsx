import { useEffect, useState } from "react";
import { Container } from "react-bootstrap";
import { GameRoom } from "./GameRoom";
import { GameRoomType, SocketOutputDto, SOCKET_GAME_EVENT } from "../../common/types";
import { myGameSocket } from "../../common/MySocket";
import "./Effect.css";

type GameRoomListType = [
    gameRoomList: GameRoomType[],
    setGameRoomList: React.Dispatch<React.SetStateAction<GameRoomType[]>>
];
type ArgsType = {
    setReceivedMsg: React.Dispatch<
        React.SetStateAction<SocketOutputDto | undefined>
    >;
}
export function GameRooms({setReceivedMsg} : ArgsType) {
    let [gameRoomList, setGameRoomList] : GameRoomListType = useState<GameRoomType[]>([]);

    useEffect(() => {
        myGameSocket.socket.emit(SOCKET_GAME_EVENT.LIST, setGameRoomList);
    }, []);

	return (
		<Container className="m-0 p-0 mb-auto Scrollable" style={{ height:"81vmin" }}>
        {
            gameRoomList.map((obj :GameRoomType, idx :number) => {
                return (
                    <GameRoom key={idx} obj={obj} setReceivedMsg={setReceivedMsg}/>
                );
            })
        }
        </Container>
	);
}