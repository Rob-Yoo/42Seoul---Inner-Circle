import { io, Socket } from 'socket.io-client'

interface MySocket {
  socket: Socket;
  name: string;
  enteredChannelName: string;
  enteredGameRoom?: boolean;
}

export let mySocket: MySocket;
export let myGameSocket: MySocket;


export function SetSocket(newName: string) {
  mySocket = {
    socket: io(`http://${process.env.REACT_APP_BACKEND_HOST}:${process.env.REACT_APP_BACKEND_PORT}/chat`, {
      withCredentials: true,
      query: {
        nickname: newName,
      },
    }),
    name: newName,
    enteredChannelName: "",
    enteredGameRoom: false,
  };
}

export function setGameSocket(newName: string) {
	myGameSocket = {
		socket: io(
			`http://${process.env.REACT_APP_BACKEND_HOST}:${process.env.REACT_APP_BACKEND_PORT}/game`,
			{
				withCredentials: true,
				query: {
					nickname: newName,
				},
			}
		),
		name: newName,
		enteredChannelName: "",
	};
}