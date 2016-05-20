#!/bin/bash

## This script is meant to act as a sort of password vault
## it's supposed to be sourced into the bash runtime for each interactive instance
## This way the functions can be called directly.

## Determine if a gpg key exists
key_check()
{
    echo "This function is supposed to check for gpg keys to sign and/or encrypt with"
}

## Create a gpg key if necessary
gen_key()
{
    echo "This function will create a gpg key for the specified user (defaults to $USER)"
}

## Add a password
add_pass()
{
    echo "Decrypt the vault and decompress it for writing"
    sleep 2
    pass_close
}

## Close the archive
pass_close()
{
    echo "re-compress the archive"
    sleep 2
    echo "re-encrypt the archive"
}

## Sign the archive
sign_vault()
{
    echo "This is the part where the archive is signed with your key"
}

## Generate a new password
gen_pass()
{
    echo "Here's where we use dd to grab random data, and sort it into printable characters."
    echo "It may even be possible to specify the total length and complexity if done correctly."
}

## Hash the vault to ensure data integrity
hash_vault()
{
    echo "here's where we run a hash over the vault to be able to verify its integrity between hosts"
}


