#!/bin/bash

sqlite3 bruker.sqlite <<EOF

DROP TABLE IF EXISTS Bruker;

CREATE TABLE Bruker (
    brukernavn varchar(20) NOT NULL,
    passord VARCHAR(50),
    uid SMALLINT NOT NULL,
    gid SMALLINT,
    navn VARCHAR(250),
    hjemmekatalog VARCHAR(100),
    kommandotolker VARCHAR(100),
    PRIMARY KEY(brukernavn),
    UNIQUE(uid)
);


.mode csv
.separator ':'
.import /etc/passwd Bruker
.exit

EOF
