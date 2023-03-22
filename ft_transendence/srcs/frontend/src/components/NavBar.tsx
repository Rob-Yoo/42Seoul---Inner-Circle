import { Button, Col, Container, Nav, Navbar, Row } from "react-bootstrap";
import { useNavigate } from "react-router-dom";
import { api } from "../axios/api";

type NavBarComponent = {
	isLoggedIn: boolean;
	setLoggedIn: (isLoggedIn: boolean) => any;
};

function NavBar({ isLoggedIn, setLoggedIn }: NavBarComponent) {
	const navigate = useNavigate();

	const logOut = async () => {
		await api.get("/logout");
		setLoggedIn(false);
		navigate("/");
		navigate(0);
	};

	return (
		<header>
			<Navbar className="border" style={{ height: "10vmin" }}>
				<Container>
					<Navbar.Brand>
						<Nav.Link onClick={() => navigate("/")} className="text-light">
							Pong Game
						</Nav.Link>
					</Navbar.Brand>
				</Container>
				<Container className="justify-content-end">
					<Nav>
						<Nav.Item>
							{isLoggedIn === false ? (
								<>
									<Button
									variant="outline-light"
									size="lg"
									onClick={() => (window.location.href = `http://${process.env.REACT_APP_BACKEND_HOST}:${process.env.REACT_APP_BACKEND_PORT}/login`)}
									>
										로그인
									</Button><Button
										variant="outline-light"
										size="lg"
										onClick={() => (window.location.href = `http://${process.env.REACT_APP_BACKEND_HOST}:${process.env.REACT_APP_BACKEND_PORT}/login/anonymous`)}
									>
										익명 로그인
									</Button>
								</>
							) : (
								<>
									<Button
										variant="outline-light"
										size="lg"
										onClick={() => navigate("/profile")}
									>
										프로필
									</Button>
									<Button variant="outline-light" size="lg" onClick={logOut}>
										로그아웃
									</Button>
								</>
							)}
						</Nav.Item>
					</Nav>
				</Container>
			</Navbar>
		</header>
	);
}

export default NavBar;
