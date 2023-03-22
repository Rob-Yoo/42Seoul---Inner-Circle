import { useRef, useState } from "react";
import { Button, Card, Form, InputGroup, Row } from "react-bootstrap";
import { BoolType, ChannelType, SocketInputDto, SocketOutputDto, SOCKET_EVENT } from "../../common/types";
import { mySocket } from "../../common/MySocket";
import "./Effect.css"

type ArgsType = {
    obj: ChannelType,
    enterChannel : (dto: SocketOutputDto) => void
};

export function Channel({obj, enterChannel} :ArgsType) {
    let [visible, setVisible] :BoolType = useState<boolean>(false);
    let name :string = (obj.password ? `🔒 ${obj.name} 🔒` : obj.name);
    const pwInputRef = useRef<HTMLInputElement>(null);

    const toJoinTheGame = () => {
        let pw :string;
        if (pwInputRef && pwInputRef.current && pwInputRef.current.value)
            pw = pwInputRef.current!.value;
        else
            pw = "";
        const dto :SocketInputDto = {
            author: mySocket.name,
            target: obj.name,
            password: pw
        };

        mySocket.socket.emit(SOCKET_EVENT.JOIN, dto, enterChannel);
        offVisible();
		if (pwInputRef && pwInputRef.current)
        	pwInputRef!.current!.value = "";
    }

    const onVisible = () => setVisible(true);
    const offVisible = () => setVisible(false);

    return (
        <Row className="mb-2 align-items-center">
            <Card
                className="CursorPointer"
                bg="dark" text="light">
                <Card.Title
                    className="m-0 text-center Dragunable"
                    onClick={ visible === true ? offVisible : onVisible }
                    >{name}
                </Card.Title>
                {
                    visible && <Card.Body className="flex-column">
                                    {
                                        obj.password && <InputGroup>
                                                            <Form.Control
                                                                placeholder="비밀번호를 입력하세요."
                                                                aria-label="With textarea"
                                                                aria-describedby="basic-addon2"
                                                                ref={pwInputRef}
                                                            />
                                                        </InputGroup>
                                    }
                                    <Button
                                        className="w-100"
                                        variant="outline-light"
                                        size="lg"
                                        onClick={toJoinTheGame}
                                        >들어가기
                                    </Button>
                                </Card.Body>
                }
            </Card>
        </Row>
    );
}
