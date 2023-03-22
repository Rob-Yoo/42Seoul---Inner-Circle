import { useEffect, useState } from "react";
import { Form, Button, Container, Card, CloseButton, Alert } from "react-bootstrap";
import { useNavigate } from "react-router-dom";
import { myGameSocket, mySocket } from "../common/MySocket";
import { BoolType } from "../common/types";

type CreatRoomType = {
	SetNeedclear: React.Dispatch<React.SetStateAction<boolean>>;
};

function CreatRoom({SetNeedclear}: CreatRoomType) {
	const navigate = useNavigate();
	const [roomName, setRoomName] = useState<string>('');
	const [password, setPassword] = useState<string>('');
	const [usePassword, setUsePassword] :BoolType = useState<boolean>(false);
	const [showWarning, setShowWarning] :BoolType = useState<boolean>(false);

	const styleEl = document.createElement('style');
	styleEl.appendChild(document.createTextNode(styles));
	document.head.appendChild(styleEl);

	const handleRoomChange = (e: React.ChangeEvent<HTMLInputElement>) => {
		const roomName = e.target.value.replace(/[^a-zA-Z0-9]/g, '').slice(0, 10);
		setRoomName(roomName);
	};

	const handlePasswordChange = (e: React.ChangeEvent<HTMLInputElement>) => {
		const password = e.target.value.replace(/[^a-zA-Z0-9]/g, '').slice(0, 10);
		setPassword(password);
	};

	const handleUsePassword = (e: React.ChangeEvent<HTMLInputElement>) => {
		setUsePassword(e.target.checked);
		if (!e.target.checked) {
			setPassword("");
		}
	};

	const handleClose = () => {
		const alert = document.querySelector('.warning-alert');
		alert?.classList.add('fade-out');
		setTimeout(() => setShowWarning(false), 100);
	}

	const handleSubmit = () => {
		let room : {roomName : string, password : string} = {roomName, password};
		if (usePassword) {
			if (roomName.length >= 4 && password.length >= 4) {
				myGameSocket.socket.emit('create-room', room, (res: any)=> {
					if (res.success) {
						navigate("/privateGame");
						mySocket.enteredGameRoom = true
					}
				})
			} else {
				setShowWarning(true);
				setTimeout(() => setShowWarning(false), 3000);
			}
		}
		else {
			if (roomName.length >= 4) {
				myGameSocket.socket.emit('create-room', room, (res: any) => {
					if (res) {
						navigate("/friendlyGame");
						mySocket.enteredGameRoom = true
					}
				})
			}
			else {
				setShowWarning(true);
				setTimeout(() => setShowWarning(false), 3000);
			}
		}
	};

	const handleClickClose = () => {
		navigate("/");
	};

	useEffect(()=> {
		SetNeedclear(true);
	}, []);

	return (
		<Container className="pt-5 mt-5">
			<Card className="bg-transparent border p-3">
				<Form>
				<CloseButton
					aria-label="Hide"
					variant="white"
					onClick={handleClickClose}
				/>;
				<Card.Body>
					<Form.Group className="mb-3" controlId="formRoomName">
						<Form.Label className="text-white">Room Name</Form.Label>
						<Form.Control
							type="text"
							placeholder="Enter Room Name"
							onChange={handleRoomChange}
							value={roomName}
							onKeyPress={(e) => /[a-zA-Z0-9!@#$%^&*()_+]/.test(e.key) || e.preventDefault()}
							className="bg-transparent text-white"
						/>
						<Form.Text className="text-muted">4 - 10 alphanumeric characters</Form.Text>
					</Form.Group>
					<Form.Group className="mb-3" controlId="password">
						<Form.Label className="text-white">PassWord</Form.Label>
						<Form.Control
							type="password"
							placeholder="Enter Password"
							className="bg-transparent text-white"
							onChange={handlePasswordChange}
							disabled={!usePassword}
							value={password}
							onKeyPress={(e) => /[a-zA-Z0-9]/.test(e.key) || e.preventDefault()}
						/>
						<Form.Text className="text-muted">
						4 - 10 alphanumeric and special characters.
					</Form.Text>
					</Form.Group>
					<Form.Group className="mb-3">
					<Form.Check className="text-white"
						required
						type="checkbox"
						label="Use Password"
						feedbackType="invalid"
						checked={usePassword}
						onChange={handleUsePassword}
						/>
					</Form.Group>
					<div className="d-flex justify-content-end">
						<Button
							onClick={handleSubmit}
							className="w-100"
							variant="outline-light">
							방만들기
						</Button>
					</div>
					</Card.Body>
				</Form>
			</Card>
			{showWarning && (
				<Alert
					variant="warning"
					onClose={handleClose}
					dismissible
					className="warning-alert"
				>
				At least four characters.
			</Alert>)}
		</Container>
	)
}

export default CreatRoom;


const styles = `
.warning-alert {
	border: 2px solid white;
	background-color: black;
	color: white;
	opacity: 1;
	transition: opacity 0.5s ease-in-out;
}

.warning-alert .alert-heading {
	color: white;
}

.warning-alert .close {
	color: white;
}

.warning-alert .close:hover {
	color: white;
	opacity: 0.75;
}

.warning-alert.fade-out {
	opacity: 0;
}
`;
