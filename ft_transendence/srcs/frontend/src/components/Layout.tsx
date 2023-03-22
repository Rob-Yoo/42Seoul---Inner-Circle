import { Col, Row, Container } from "react-bootstrap";
import ChatPart from "./chatting/ChatPart";
import { useNavigate, useParams } from "react-router-dom";
import Home from "./Home";
import Game from "./game/Game";
import CreatRoom from "./Room";
import Profile from "./Profile/Profile";
import MyInform from "./Information/MyInform";
import { GameData, gameMod, UserData } from "../common/types";
import { useEffect, useState } from "react";
import { myGameSocket, mySocket } from "../common/MySocket";

type LayoutComponent = {
	isLoggedIn: boolean;
	userData: UserData;
	gameData: GameData[] | undefined;
	isChangedData: boolean;
	setChangedData: React.Dispatch<React.SetStateAction<boolean>>;
	isChangedGameData: boolean;
	setChangedGameData: React.Dispatch<React.SetStateAction<boolean>>;
};

const min_width = 2400;

function Layout({
	isLoggedIn,
	userData,
	gameData,
	isChangedData,
	setChangedData,
	isChangedGameData,
	setChangedGameData,
}: LayoutComponent) {
	const [inform, setInform] = useState<UserData>();
	const [enteredChannel, setEnteredChannel] = useState<boolean>(false);
	const url = useParams();
	const param = url["*"];
	const navigate = useNavigate();
	const [needClear, SetNeedclear] = useState<boolean>(true);
	const [windowWidth, setWindowWidth] = useState(window.innerWidth);
	useEffect(() => {
		function handleResize() {
			setWindowWidth(window.innerWidth);
		}
		window.addEventListener("resize", handleResize);
		return () => {
			window.removeEventListener("resize", handleResize);
		};
	}, []);


	const getComponent = () => {
		if (param === "") {
			if (myGameSocket && needClear) {
				myGameSocket.socket.emit('clear');
				mySocket.enteredGameRoom = false;
				SetNeedclear(false);
			}
			return (
				<Home
				isLoggedIn={isLoggedIn}
				userData={userData}
				enteredChannel={enteredChannel}
				/>
			);
		}
		else if (param === "profile")
			return (
				<Profile
					isLoggedIn={isLoggedIn}
					userData={userData}
					isChangedData={isChangedData}
					setChangedData={setChangedData}
				/>
			);
		else if (param === "soloGame") return <Game mod={gameMod.soloGame} isChangedGameData={isChangedData} setChangedGameData={setChangedData} SetNeedclear={SetNeedclear}/>;
		else if (param === "rankGame") return <Game mod={gameMod.rankGame} isChangedGameData={isChangedData} setChangedGameData={setChangedData} SetNeedclear={SetNeedclear} />;
		else if (param === "friendlyGame") return <Game mod={gameMod.normalGame} isChangedGameData={isChangedData} setChangedGameData={setChangedData} SetNeedclear={SetNeedclear} />;
		else if (param === "watchGame") return <Game mod={gameMod.watchGame} isChangedGameData={isChangedData} setChangedGameData={setChangedData} SetNeedclear={SetNeedclear} />;
		else if (param === "privateGame")
			return <Game mod={gameMod.passwordGame} isChangedGameData={isChangedData} setChangedGameData={setChangedData} SetNeedclear={SetNeedclear} />;
		else if (param === "creatGame") return <CreatRoom  SetNeedclear={SetNeedclear}/>;
		else navigate("/");
	};

	const getBorder = () => {
		if (isLoggedIn) return "border";
		else return "";
	};

	return (
		<>
			<Container fluid style={{ height: "90vmin" }}>
				<Row
					style={{
						height: "90vmin",
						display: "flex",
						justifyContent: "center",
					}}
				>
					{windowWidth > min_width && (
						<Col xs={3} className={getBorder()}>
							{userData.nickname === null || !isLoggedIn ? null : (
								<MyInform
									inform={inform ?? userData}
 									setInform={setInform}
 									myData={userData}
 								/>
 							)}
 						</Col>
					)}
					<Col xs={6}>{getComponent()}</Col>
					{windowWidth > min_width && (
						<Col xs={3} className={getBorder()}>
							{isLoggedIn && (
								<ChatPart
									setInform={setInform}
									setEnteredChannel={setEnteredChannel}
								/>
							)}
						</Col>
					)}
				</Row>
			</Container>
		</>
	);
}

export default Layout;
