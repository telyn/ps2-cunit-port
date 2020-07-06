FROM ps2dev

COPY ./install-cunit.sh /install-cunit.sh
RUN /install-cunit.sh
