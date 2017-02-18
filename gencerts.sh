#!/bin/bash

mkdir keys
openssl req -x509 -newkey rsa:4096 -keyout keys/cakey.pem -out keys/cacert.pem -days 365
