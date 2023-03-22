import { useEffect, useState } from "react";
import { Container } from "react-bootstrap";
import { Channel } from "./Channel";
import { ChannelType, SocketOutputDto, SOCKET_EVENT } from "../../common/types";
import { mySocket } from "../../common/MySocket";
import "./Effect.css";

type channelListType = [
    channelList: ChannelType[],
    setChannelList: React.Dispatch<React.SetStateAction<ChannelType[]>>
];

export function Channels({enterChannel} : { enterChannel : (dto: SocketOutputDto) => void }) {
    let [channelList, setChannelList] : channelListType = useState<ChannelType[]>([]);

    useEffect(() => {
        mySocket.socket.emit(SOCKET_EVENT.GET_CHANNEL, setChannelList);
    }, []);

	return (
		<Container className="m-0 p-0 mb-auto Scrollable" style={{ height:"81vmin" }}>
        {
            channelList.map((obj :ChannelType, idx :number) => {
                return (
                    <Channel key={idx} obj={obj} enterChannel={enterChannel}/>
                );
            })
        }
        </Container>
	);
}