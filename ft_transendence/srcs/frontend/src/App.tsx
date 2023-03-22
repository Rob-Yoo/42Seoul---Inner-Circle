import { useState, useEffect } from "react";
import NavBar from "./components/NavBar";
import Layout from "./components/Layout";
import { Route, Routes, useNavigate } from "react-router-dom";
import { api } from "./axios/api";
import { BoolType, GameData, UserData } from "./common/types";
import {
	mySocket,
	myGameSocket,
	SetSocket,
	setGameSocket,
} from "./common/MySocket";

const min_height = 500;

function App() {
	const navigate = useNavigate();
	const [loggedIn, setLoggedIn]: BoolType = useState<boolean>(false);
	let [userData, setUserData] = useState<UserData>({
		intra: "",
		usual_full_name: "",
		nickname: "",
		phone: "",
		verified: false,
		avatarId: 0,
	});
	let [gameData, setGameData] = useState<GameData[]>();
	const [isChangedData, setChangedData]: BoolType = useState<boolean>(false);
	const [isChangedGameData, setChangedGameData]: BoolType = useState<boolean>(false);
	const [windowHeight, setWindowHeight] = useState(window.innerHeight);

 	useEffect(() => {
 		function handleResize() {
 			setWindowHeight(window.innerHeight);
 		}
 		window.addEventListener("resize", handleResize);
 		return () => {
 			window.removeEventListener("resize", handleResize);
 		};
 	}, []);

	const getUserData = async () => {
		try {
			const res = await api.get("/user/me");
			const { user } = res.data;
			const data: UserData = {
				intra: user.intra,
				usual_full_name: user.usual_full_name,
				nickname: user.nickname,
				phone: user.phone,
				verified: user.verified,
				avatarId: user.avatarId,
			};
			setUserData(data);
			if (mySocket)
				mySocket.name = user?.nickname;
		} catch (e) {
			console.error(e);
		}
	};

	const getGameData = async () => {
		try {
			const res = await api.get(`/game/history?nickname=${userData.nickname}`);
			let record: GameData[] = [];
			res.data?.history?.sort((h:any) => -new Date(h.createdAt).valueOf());
			for (let i = 0; i < res.data?.history?.length; i++) {
				let WinCheck : boolean;
				let RankCheck : boolean = true;
				let opponent : string;
				const dateObject = new Date(res.data?.history[i].createdAt);
				if (res.data?.history[i].winner === userData.nickname) {
					WinCheck = true;
					opponent = res.data?.history[i].loser;
				}
				else {
					WinCheck = false;
					opponent = res.data?.history[i].winner;
				}
				if (res.data?.history[i].type !== 3)
					RankCheck = false;
				let rec : GameData = {
					timestamp : dateObject.toLocaleTimeString(),
					nickname: opponent,
					isRank : RankCheck,
					isWin : WinCheck,
				}
				record.push(rec);
			}
			setGameData(record);
		} catch (e) {
			console.error(e);
		}
	};

	const intraLogin = async () => {
		try {
			const res = await api.get("/user/me");
			const { user } = res.data;
			const data: UserData = {
				intra: user.intra,
				usual_full_name: user.usual_full_name,
				nickname: user.nickname,
				phone: user.phone,
				verified: user.verified,
				avatarId: user.avatarId,
			};
			setLoggedIn(true);
			setUserData(data);
			mySocket === undefined && SetSocket(data.nickname);
			/////////////////////////////
			getGameData();
			myGameSocket === undefined && setGameSocket(data.nickname);
			if (myGameSocket) {
				myGameSocket.socket.emit("nickname", data.nickname);
			}
			//////////////////////////////
			if (data.nickname === null && data.phone === null) navigate("/profile");
		} catch (e) {
			setLoggedIn(false);
			setUserData({
				intra: "",
				usual_full_name: "",
				nickname: "",
				phone: "",
				verified: false,
				avatarId: 0,
			});
		}
	};

	useEffect(() => {
		intraLogin();
		getGameData();
	// eslint-disable-next-line react-hooks/exhaustive-deps
	}, [loggedIn, isChangedGameData]);

	useEffect(() => {
		getUserData();
	}, [isChangedData]);


	return (
		<>
			{windowHeight > min_height && <NavBar isLoggedIn={loggedIn} setLoggedIn={setLoggedIn} />}
			<Routes>
				<Route
					path="/*"
					element={
						<Layout
							isLoggedIn={loggedIn}
							userData={userData}
							gameData={gameData}
							isChangedData={isChangedData}
							setChangedData={setChangedData}
							isChangedGameData={isChangedGameData}
							setChangedGameData={setChangedGameData}
						/>
					}
				/>
			</Routes>
		</>
	);
}

export default App;
