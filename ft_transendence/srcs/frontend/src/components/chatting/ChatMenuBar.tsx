import { Container, Button, Col, Row } from "react-bootstrap";
import { ENTER_CHANNEL, SHOW_OTHER, SHOW_CHATROOM } from "../../common/types";

const CHANNEL: string = "Channel";
const GAMEROOM: string = "GameRoom";
const CHATROOM: string = "Chatting";

type Flags = {
	flag: boolean;
	setFlag: React.Dispatch<React.SetStateAction<boolean>>;
	enterChannelFlag: boolean;
	exitChannel: () => void;
};

export function ChatMenuBar({
	flag,
	setFlag,
	enterChannelFlag,
	exitChannel,
}: Flags) {
	return (
		<Container className="pt-3 px-0" style={{ height: "8vmin" }}>
			<Row className="px-3 text-center align-items-center">
				<Col className="text-center align-items-center">
					<h4 style={{ color: "white", padding: "0", margin: "0" }}>
						{flag === SHOW_CHATROOM
							? CHATROOM
							: enterChannelFlag === ENTER_CHANNEL
							? GAMEROOM
							: CHANNEL}
					</h4>
				</Col>
				<Col md={6} className="p-0">
					{enterChannelFlag === ENTER_CHANNEL && (
						<Button variant="outline-light" size="lg" onClick={exitChannel}>
							나가기
						</Button>
					)}
					<Button
						variant="outline-light"
						size="lg"
						onClick={() => {
							flag !== SHOW_CHATROOM
								? setFlag(SHOW_CHATROOM)
								: setFlag(SHOW_OTHER);
						}}
					>
						{flag !== SHOW_CHATROOM
							? CHATROOM
							: enterChannelFlag === ENTER_CHANNEL
							? GAMEROOM
							: CHANNEL}
					</Button>
				</Col>
			</Row>
			<Row className="pt-3">
				<hr style={{ color: "white" }} />
			</Row>
		</Container>
	);
}
