#docker build -t shitos .
docker run -v "$(pwd)"/kernel:/kernel -it shitos
