import { Button, Modal } from "react-bootstrap";

type modalComponent = {
	cvomShow: boolean;
	setCVOModalShow: (cvomShow: boolean) => any;
	setCertificated: (c: boolean) => any;
};

function CheckVerifyingOffModal({
	cvomShow,
	setCVOModalShow,
	setCertificated,
}: modalComponent) {
	const handleCancel = () => {
		setCVOModalShow(false);
	};
	const handleCheck = () => {
		setCertificated(false);
		setCVOModalShow(false);
	};
	return (
		<Modal
			show={cvomShow}
			onHide={() => setCVOModalShow(false)}
			aria-labelledby="contained-modal-title-vcenter"
			dialogClassName="modal-50w"
			centered
		>
			<Modal.Header closeButton>
				<Modal.Title id="contained-modal-title-vcenter">주의</Modal.Title>
			</Modal.Header>
			<Modal.Body>
				2차 인증 상태가 off 모드이면 서비스가 제한될 수 있습니다. <br />
				off 모드로 변경하시겠습니까?
			</Modal.Body>
			<Modal.Footer>
				<Button onClick={handleCancel} className="btn-secondary">
					취소
				</Button>
				<Button onClick={handleCheck} className="btn-danger">
					확인
				</Button>
			</Modal.Footer>
		</Modal>
	);
}

export default CheckVerifyingOffModal;
