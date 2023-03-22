import { useState } from "react";
import { Modal, Button, Form } from "react-bootstrap";
import { api } from "../../axios/api";

type modalComponent = {
	vcmShow: boolean;
	setVCModalShow: (vcmShow: boolean) => any;
	setCertificated: (isCertificated: boolean) => any;
};

function VerifyingCodeModal({
	vcmShow,
	setVCModalShow,
	setCertificated,
}: modalComponent) {
	const [code, setCode] = useState("");

	const handleSubmit = async () => {
		if (code === "" || code === undefined || code === null)
			alert("코드를 입력해주세요.");
		else if (code.length !== 6 || !Number(code))
			alert("코드 형식이 올바르지 않습니다");
		else {
			try {
				const res = await api.post(`/tfa/verify?code=${code}`);
				const { ok } = res.data;
				if (ok === true) {
					setCertificated(true);
					setVCModalShow(false);
				} else {
					alert("올바르지 않는 코드입니다.");
				}
			} catch (e) {
				console.error(e);
			}
		}
	};
	return (
		<Modal
			show={vcmShow}
			onHide={() => setVCModalShow(false)}
			aria-labelledby="contained-modal-title-vcenter"
			dialogClassName="modal-50w"
			centered
		>
			<Modal.Header closeButton>
				<Modal.Title id="contained-modal-title-vcenter">2차 인증</Modal.Title>
			</Modal.Header>
			<Modal.Body>
				<Form>
					<Form.Group className="mb-3" controlId="TwoFactorVerifying">
						<Form.Label>코드 입력</Form.Label>
						<Form.Control
							type="text"
							placeholder="6자리 코드 입력"
							pattern="[0-9]{6}"
							value={code}
							onChange={(e) => setCode(e.target.value)}
							onKeyDown={(e) => {
								if (e.key === "Enter") e.preventDefault();
							}}
						/>
					</Form.Group>
				</Form>
			</Modal.Body>
			<Modal.Footer>
				<Button onClick={handleSubmit}>확인</Button>
			</Modal.Footer>
		</Modal>
	);
}

export default VerifyingCodeModal;
