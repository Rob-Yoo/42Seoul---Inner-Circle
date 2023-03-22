import { Button, Card, Col, Container, Form, Row } from "react-bootstrap";
import { UserData } from "../../common/types";

type ShowProfileComponent = {
	userData: UserData;
	setEdit: (edit: boolean) => any;
};

function ShowProfile({ userData, setEdit }: ShowProfileComponent) {
	return (
		<>
			<Container className="pt-5">
				<Card className="bg-transparent border p-3">
					<Card.Body>
						<Card.Title className="text-white">프로필</Card.Title>
						<Form className="border-top p-4">
							<Form.Group className="mb-3" controlId="formIntraID">
								<Form.Label className="text-white">인트라 ID</Form.Label>
								<Form.Control
									type="text"
									placeholder="Intra ID"
									className="bg-transparent text-white"
									value={`${userData.intra}`}
									disabled
								/>
							</Form.Group>
							<Form.Group className="mb-3" controlId="formName">
								<Form.Label className="text-white">이름</Form.Label>
								<Form.Control
									type="text"
									placeholder="Name"
									className="bg-transparent text-white"
									value={`${userData.usual_full_name}`}
									disabled
								/>
							</Form.Group>
							<Row>
								<Col>
									<Form.Group className="mb-3" controlId="formNickName">
										<Form.Label className="text-white">닉네임</Form.Label>
										<Form.Control
											type="text"
											placeholder="Nickname"
											className="bg-transparent text-white"
											value={userData.nickname}
											disabled
										/>
									</Form.Group>
								</Col>
							</Row>
							<Form.Group className="mb-3" controlId="formPhoneNumber">
								<Form.Label className="text-white">전화번호</Form.Label>
								<Form.Control
									type="tel"
									placeholder="'-' 없이 숫자만 입력"
									pattern="[0-9]{3}[0-9]{4}[0-9]{4}"
									className="bg-transparent text-white"
									value={userData.phone}
									disabled
								/>
							</Form.Group>
							<Form.Check
								type="switch"
								id="custom-switch"
								label="2차 인증"
								className="text-white"
								checked={userData.verified}
								disabled
							/>
							<Container className="pt-3">
								<Row className="mt-3">
									<Button variant="outline-light" onClick={() => setEdit(true)}>
										변경하기
									</Button>
								</Row>
							</Container>
						</Form>
					</Card.Body>
				</Card>
			</Container>
		</>
	);
}

export default ShowProfile;
