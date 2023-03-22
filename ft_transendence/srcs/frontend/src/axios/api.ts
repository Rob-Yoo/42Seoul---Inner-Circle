import axios from "axios";

export const api = axios.create({
	baseURL: `http://${process.env.REACT_APP_BACKEND_HOST}:${process.env.REACT_APP_BACKEND_PORT}`,
	withCredentials: true,
});
