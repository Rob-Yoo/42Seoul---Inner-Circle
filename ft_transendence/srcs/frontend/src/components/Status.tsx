import { useEffect, useState } from "react";
import { Badge, ListGroup, Offcanvas } from "react-bootstrap";
import { myGameSocket, mySocket } from "../common/MySocket";

type StatusComponent = {
	friend: string;
};

enum STATUS{
	GAMING = "success",
	ONLINE = "primary",
	OFFLINE = "secondary",
}

function Status({ friend }: StatusComponent) {
	const [status, setStatus] = useState<STATUS>(STATUS.OFFLINE);
	const [refresh, setRefresh] = useState<boolean>(true);

	useEffect(()=>{
		mySocket.socket.on('refresh-status', ()=>{
			setRefresh(prev=>!prev);
		})
		myGameSocket.socket.on('refresh-status', ()=>{
			setRefresh(prev=>!prev);
		})

		return () => {
			mySocket.socket.off('refresh-status');
			myGameSocket.socket.off('refresh-status');
		}
	}, [])

	useEffect(()=>{
		checkStatus(friend);
	}, [refresh])

	const checkStatus = (friend : string) => {
		myGameSocket.socket.emit('check-status', friend, (s :boolean) => {
			if (s)
				setStatus(STATUS.GAMING);
			else {
				mySocket.socket.emit('check-status', friend, (s :boolean) => {
					if(s)
						setStatus(STATUS.ONLINE);
					else
						setStatus(STATUS.OFFLINE);
				});
			}
		});
	}

	return (
		<Badge bg={status}
			className="rounded-circle" style={{height: "1.5vmin", width: "1.5vmin"}}>
			<p></p>
		</Badge>
	);
}

export default Status;
