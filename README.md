# htcpcp-senseo
HTCPCP server implementation for Philips Senseo

This project is an implementation of HTCPCP 1.0, as [described in RFC 2324](https://www.ietf.org/rfc/rfc2324.txt), in a Philips Senseo coffee machine.
It uses a arduino with ethernet shield as CoIP (coffee over IP) controller.

## Features
To be descrided.

## Supported methods
#### GET
Implemented. To be documented.

#### POST and BREW
Implemented. To be documented.

#### PROPFIND
Not implemented due to hardware limitation of this coffee machine.
Will return a `501 Not Implemented` error code.

#### WHEN
Not implemented. This coffee machine has auto-off.
Will return a `501 Not Implemented` error code.

## Supported headers
Due to hardware limitation of this coffee machine headers field `Accept-Additions` will always return a empty value and `addition-type`, `syrup-type`, `milk-type` and `alcohol-type` will never be used.

## Error codes
* `200 OK`
* `406 Not Acceptable Here`: wait for coffee machine heating or check water tank
* `500 Internal Error`
* `501 Not Implemented`
