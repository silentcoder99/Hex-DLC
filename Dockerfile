FROM base/archlinux:latest

ADD build/server/Hex-DLCServer /usr/bin/hex

EXPOSE 20046 

RUN pacman -Sy && \
    pacman -S archlinux-keyring --noconfirm && \
    pacman -S boost gcc --noconfirm 

ENTRYPOINT ["/usr/bin/hex"]
