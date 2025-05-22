#!/bin/bash

FILENAME=$1
USER=$(whoami)
DATE=$(date +"%Y/%m/%d %H:%M:%S")

if [ -z "$FILENAME" ]; then
    echo "Usage: ./add_header.sh filename.c"
    exit 1
fi

HEADER=$(cat <<EOF
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   $(printf "%-51s" "$(basename $FILENAME)"):+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: $(printf "%-42s" "$LOGIN <$EMAIL>")+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: $(printf "%-20s" "$DATE by $LOGIN")#+#    #+#             */
/*   Updated: $(printf "%-20s" "$DATE by $LOGIN")###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
EOF
)

echo "$HEADER" | cat - "$FILENAME" > temp && mv temp "$FILENAME"

