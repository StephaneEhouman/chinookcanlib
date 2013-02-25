# ChinookCan


## Protocol Definition

Definition of our custom can protocol


### Fields

    {
      can id,
      can length,
      data field:{
        action,
        data
       }
    }

Protocol segmentation in bits

    ... | can id | ... | length | ... |  data field   |
    ... |   11   | ... |   4    | ... |     1 - 64    |
    ... |        | ... |        | ... | action | data |
    ... |        | ... |        | ... |    8   | 1-56 |

    **size in bit**

### CAN identifier (can standard)

CAN id is used to represent the physical or logical device is being sent or publishing data

### CAN length (can standard)

CAN length is a standard field in can and is used to represent the number of bytes in the Can message part

### CAN data field (can standard)

CAN message part is the actual content of the CAN


#### Chinook Action Field

The action the message wants to do.

    0x01  Get
    0x02  Set


#### Chinook Data Field

The actual data to be transmitted. Transmitted using a simplified messagepack format.
