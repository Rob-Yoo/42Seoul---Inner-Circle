import { useEffect, useState } from "react";
import { Badge, ListGroup, Offcanvas } from "react-bootstrap";
import { myGameSocket, mySocket } from "../common/MySocket";
import { UserData } from "../common/types";
import Status from "./Status";

type FriendsComponent = {
	show: boolean;
	handleClose: () => void;
	friends: UserData[];
};

enum STATUS{
	GAMING = "success",
	ONLINE = "primary",
	OFFLINE = "secondary",
}

function Friends({ show, handleClose, friends }: FriendsComponent) {
	return (
		<Offcanvas show={show} onHide={handleClose} style={{ overflowY: "scroll" }}>
			<Offcanvas.Header closeButton>
				<Offcanvas.Title>친구 목록</Offcanvas.Title>
			</Offcanvas.Header>
			{friends.length === 0 ? (
				<Offcanvas.Body className="text-muted d-flex align-items-center justify-content-center">
					친구가 없습니다. 친구를 추가해보세요!
				</Offcanvas.Body>
			) : (
				<Offcanvas.Body>
					<ListGroup variant="flush">
						{friends.map((friend, index) =>
						<ListGroup.Item className="d-flex justify-content-between" key={index}>
							<Status friend={friend.nickname}></Status>
							{friend.nickname}
							{/* Status에 따른 색 추가 */}
						</ListGroup.Item>
					)}
					</ListGroup>
				</Offcanvas.Body>
			)}
		</Offcanvas>
	);
}

export default Friends;
