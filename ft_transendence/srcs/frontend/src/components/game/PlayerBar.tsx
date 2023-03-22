import { useEffect, useState } from 'react';
import { api } from '../../axios/api';
import { gameMod, playerType } from '../../common/types';

type gameComponent = {
	mod: gameMod;
	playerInfo : playerType | undefined;
};

interface player {
	name: string | undefined;
	wins: number;
	losses: number;
}

function Player({ mod, playerInfo }: gameComponent) {
	const [lplayer, setLPlayer] = useState<player | null>(null);
	const [rplayer, setRPlayer] = useState<player | null>(null);
	const [leftUrl, setLeftUrl] = useState<string>();
	const [rightUrl, setRightUrl] = useState<string>();

	useEffect(() => {
	if (mod !== gameMod.soloGame) {
		const getLPlayer = async () => {
			let name;
			let wins: number = 0;
			let losses: number = 0;
			if (playerInfo?.p1.nickname)
				name = playerInfo?.p1.nickname;
			else
				name = "user";
			if (playerInfo?.p1.avatarId) {
				await api
				.get(`/user/avatar/${playerInfo?.p1.avatarId}`, { responseType: "arraybuffer" })
				.then((response) => {
					const arrayBufferView = new Uint8Array(response.data);
					const blob = new Blob([arrayBufferView], { type: "image/jpeg" });
					const urlCreator = window.URL || window.webkitURL;
					const imageUrl = urlCreator.createObjectURL(blob);
					setLeftUrl(imageUrl);
				})
				.catch((error) => console.error(error));
			}
			else
				setLeftUrl("./Anonymous.jpeg");
			try {
				const res = await api.get(`/user/score?nickname=${playerInfo?.p1.nickname}`);
				if (mod === gameMod.rankGame) {
					wins = res.data?.score.r_win;
					losses = res.data?.score.r_lose;
				}
				else {
					wins = res.data?.score.f_win;
					losses = res.data?.score.f_lose;
				}
			} catch (e) {
				console.error(e);
			}
			setLPlayer({ name, wins, losses });
		};

		const getRPlayer = async () => {
			let name;
			let wins: number = 0;
			let losses: number = 0;
			if (playerInfo?.p2.nickname)
				name = playerInfo?.p2.nickname;
			else
				name = "user";
			if (playerInfo?.p2.avatarId) {
				await api
				.get(`/user/avatar/${playerInfo?.p2.avatarId}`, { responseType: "arraybuffer" })
				.then((response) => {
					const arrayBufferView = new Uint8Array(response.data);
					const blob = new Blob([arrayBufferView], { type: "image/jpeg" });
					const urlCreator = window.URL || window.webkitURL;
					const imageUrl = urlCreator.createObjectURL(blob);
					setRightUrl(imageUrl);
				})
				.catch((error) => console.error(error));
			}
			else
				setRightUrl("./Anonymous.jpeg");
				try {
					const res = await api.get(`/user/score?nickname=${playerInfo?.p2.nickname}`);
					if (mod === gameMod.rankGame) {
						wins = res.data?.score.r_win;
						losses = res.data?.score.r_lose;
					}
					else {
						wins = res.data?.score.f_win;
						losses = res.data?.score.f_lose;
					}
				} catch (e) {
					console.error(e);
				}
			setRPlayer({ name, wins, losses });
		};
		getLPlayer();
		getRPlayer();
	}

	}, []);

	return (
		<>
		{lplayer && rplayer && (
		<div style={{ display: "flex", height: "120px", color: "white" }}>
		<div style={{ display: "flex", flex: "1" }}>
		<div style={{ width: "120px", height: "120px", overflow: "hidden", borderRadius: "50%", marginRight: "20px" }}>
			<img src={leftUrl} alt="Avatar" style={{ width: "100%" }} />
		</div>
		<div>
			<h2 style={{ fontSize: '2rem', margin: 0 }}>{lplayer.name}</h2>
			<p style={{ fontSize: '1.5rem', margin: 0 }}>Wins: {lplayer.wins}</p>
			<p style={{ fontSize: '1.5rem', margin: 0 }}>Losses: {lplayer.losses}</p>
		</div>
		</div>
		<div style={{ width: "120px", display: "flex", alignItems: "flex-end" }}>
		</div>
		<div style={{ flex: "1", display: "flex", flexDirection: "column", alignItems: "flex-end" }}>
		<div style={{ textAlign: "right", paddingRight: "20px" }}>
			<h2 style={{ fontSize: '2rem', margin: 0 }}>{rplayer.name}</h2>
			<p style={{ fontSize: '1.5rem', margin: 0 }}>Wins: {rplayer.wins}</p>
			<p style={{ fontSize: '1.5rem', margin: 0 }}>Losses: {rplayer.losses}</p>
		</div>
		</div>
		<div style={{ width: "120px", height: "120px", overflow: "hidden", borderRadius: "50%" }}>
			<img src={rightUrl} alt="Avatar" style={{ width: "100%" }} />
		</div>
		</div>
		)}
		</>
	);
}

export default Player;
