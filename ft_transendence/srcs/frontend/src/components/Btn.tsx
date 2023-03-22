import { Button } from "react-bootstrap";

type BtnProps = {
	text: string;
	disable: boolean;
};

function Btn({ text, disable }: BtnProps) {
	return (
		<>
			<Button variant="outline-light" disabled={!disable}
			style={{ width: "100px", height: "50px",}} >
				{text}
			</Button>
		</>
	);
}

export default Btn;
