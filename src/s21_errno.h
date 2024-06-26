#ifndef S21_ERRORS
#define S21_ERRORS

#define ER_MAC(s, x)                                           \
  ({                                                           \
    switch (x) {                                               \
      case 1:                                                  \
        s = "Operation not permitted";                         \
        break;                                                 \
      case 2:                                                  \
        s = "No such file or directory";                       \
        break;                                                 \
      case 3:                                                  \
        s = "No such process";                                 \
        break;                                                 \
      case 4:                                                  \
        s = "Interrupted system call";                         \
        break;                                                 \
      case 5:                                                  \
        s = "Input/output error";                              \
        break;                                                 \
      case 6:                                                  \
        s = "Device not configured";                           \
        break;                                                 \
      case 7:                                                  \
        s = "Argument list too long";                          \
        break;                                                 \
      case 8:                                                  \
        s = "Exec format error";                               \
        break;                                                 \
      case 9:                                                  \
        s = "Bad file descriptor";                             \
        break;                                                 \
      case 10:                                                 \
        s = "No child processes";                              \
        break;                                                 \
      case 11:                                                 \
        s = "Resource deadlock avoided";                       \
        break;                                                 \
      case 12:                                                 \
        s = "Cannot allocate memory";                          \
        break;                                                 \
      case 13:                                                 \
        s = "Permission denied";                               \
        break;                                                 \
      case 14:                                                 \
        s = "Bad address";                                     \
        break;                                                 \
      case 15:                                                 \
        s = "Block device required";                           \
        break;                                                 \
      case 16:                                                 \
        s = "Resource busy";                                   \
        break;                                                 \
      case 17:                                                 \
        s = "File exists";                                     \
        break;                                                 \
      case 18:                                                 \
        s = "Cross-device link";                               \
        break;                                                 \
      case 19:                                                 \
        s = "Operation not supported by device";               \
        break;                                                 \
      case 20:                                                 \
        s = "Not a directory";                                 \
        break;                                                 \
      case 21:                                                 \
        s = "Is a directory";                                  \
        break;                                                 \
      case 22:                                                 \
        s = "Invalid argument";                                \
        break;                                                 \
      case 23:                                                 \
        s = "Too many open files in system";                   \
        break;                                                 \
      case 24:                                                 \
        s = "Too many open files";                             \
        break;                                                 \
      case 25:                                                 \
        s = "Inappropriate ioctl for device";                  \
        break;                                                 \
      case 26:                                                 \
        s = "Text file busy";                                  \
        break;                                                 \
      case 27:                                                 \
        s = "File too large";                                  \
        break;                                                 \
      case 28:                                                 \
        s = "No space left on device";                         \
        break;                                                 \
      case 29:                                                 \
        s = "Illegal seek";                                    \
        break;                                                 \
      case 30:                                                 \
        s = "Read-only file system";                           \
        break;                                                 \
      case 31:                                                 \
        s = "Too many links";                                  \
        break;                                                 \
      case 32:                                                 \
        s = "Broken pipe";                                     \
        break;                                                 \
      case 33:                                                 \
        s = "Numerical argument out of domain";                \
        break;                                                 \
      case 34:                                                 \
        s = "Result too large";                                \
        break;                                                 \
      case 35:                                                 \
        s = "Resource temporarily unavailable";                \
        break;                                                 \
      case 36:                                                 \
        s = "Operation now in progress";                       \
        break;                                                 \
      case 37:                                                 \
        s = "Operation already in progress";                   \
        break;                                                 \
      case 38:                                                 \
        s = "Socket operation on non-socket";                  \
        break;                                                 \
      case 39:                                                 \
        s = "Destination address required";                    \
        break;                                                 \
      case 40:                                                 \
        s = "Message too long";                                \
        break;                                                 \
      case 41:                                                 \
        s = "Protocol wrong type for socket";                  \
        break;                                                 \
      case 42:                                                 \
        s = "Protocol not available";                          \
        break;                                                 \
      case 43:                                                 \
        s = "Protocol not supported";                          \
        break;                                                 \
      case 44:                                                 \
        s = "Socket type not supported";                       \
        break;                                                 \
      case 45:                                                 \
        s = "Operation not supported";                         \
        break;                                                 \
      case 46:                                                 \
        s = "Protocol family not supported";                   \
        break;                                                 \
      case 47:                                                 \
        s = "Address family not supported by protocol family"; \
        break;                                                 \
      case 48:                                                 \
        s = "Address already in use";                          \
        break;                                                 \
      case 49:                                                 \
        s = "Can't assign requested address";                  \
        break;                                                 \
      case 50:                                                 \
        s = "Network is down";                                 \
        break;                                                 \
      case 51:                                                 \
        s = "Network is unreachable";                          \
        break;                                                 \
      case 52:                                                 \
        s = "Network dropped connection on reset";             \
        break;                                                 \
      case 53:                                                 \
        s = "Software caused connection abort";                \
        break;                                                 \
      case 54:                                                 \
        s = "Connection reset by peer";                        \
        break;                                                 \
      case 55:                                                 \
        s = "No buffer space available";                       \
        break;                                                 \
      case 56:                                                 \
        s = "Socket is already connected";                     \
        break;                                                 \
      case 57:                                                 \
        s = "Socket is not connected";                         \
        break;                                                 \
      case 58:                                                 \
        s = "Can't send after socket shutdown";                \
        break;                                                 \
      case 59:                                                 \
        s = "Too many references: can't splice";               \
        break;                                                 \
      case 60:                                                 \
        s = "Operation timed out";                             \
        break;                                                 \
      case 61:                                                 \
        s = "Connection refused";                              \
        break;                                                 \
      case 62:                                                 \
        s = "Too many levels of symbolic links";               \
        break;                                                 \
      case 63:                                                 \
        s = "File name too long";                              \
        break;                                                 \
      case 64:                                                 \
        s = "Host is down";                                    \
        break;                                                 \
      case 65:                                                 \
        s = "No route to host";                                \
        break;                                                 \
      case 66:                                                 \
        s = "Directory not empty";                             \
        break;                                                 \
      case 67:                                                 \
        s = "Too many processes";                              \
        break;                                                 \
      case 68:                                                 \
        s = "Too many users";                                  \
        break;                                                 \
      case 69:                                                 \
        s = "Disc quota exceeded";                             \
        break;                                                 \
      case 70:                                                 \
        s = "Stale NFS file handle";                           \
        break;                                                 \
      case 71:                                                 \
        s = "Too many levels of remote in path";               \
        break;                                                 \
      case 72:                                                 \
        s = "RPC struct is bad";                               \
        break;                                                 \
      case 73:                                                 \
        s = "RPC version wrong";                               \
        break;                                                 \
      case 74:                                                 \
        s = "RPC prog. not avail";                             \
        break;                                                 \
      case 75:                                                 \
        s = "Program version wrong";                           \
        break;                                                 \
      case 76:                                                 \
        s = "Bad procedure for program";                       \
        break;                                                 \
      case 77:                                                 \
        s = "No locks available";                              \
        break;                                                 \
      case 78:                                                 \
        s = "Function not implemented";                        \
        break;                                                 \
      case 79:                                                 \
        s = "Inappropriate file type or format";               \
        break;                                                 \
      case 80:                                                 \
        s = "Authentication error";                            \
        break;                                                 \
      case 81:                                                 \
        s = "Need authenticator";                              \
        break;                                                 \
      case 82:                                                 \
        s = "Device power is off";                             \
        break;                                                 \
      case 83:                                                 \
        s = "Device error";                                    \
        break;                                                 \
      case 84:                                                 \
        s = "Value too large to be stored in data type";       \
        break;                                                 \
      case 85:                                                 \
        s = "Bad executable (or shared library)";              \
        break;                                                 \
      case 86:                                                 \
        s = "Bad CPU type in executable";                      \
        break;                                                 \
      case 87:                                                 \
        s = "Shared library version mismatch";                 \
        break;                                                 \
      case 88:                                                 \
        s = "Malformed Mach-o file";                           \
        break;                                                 \
      case 89:                                                 \
        s = "Operation canceled";                              \
        break;                                                 \
      case 90:                                                 \
        s = "Identifier removed";                              \
        break;                                                 \
      case 91:                                                 \
        s = "No message of desired type";                      \
        break;                                                 \
      case 92:                                                 \
        s = "Illegal byte sequence";                           \
        break;                                                 \
      case 93:                                                 \
        s = "Attribute not found";                             \
        break;                                                 \
      case 94:                                                 \
        s = "Bad message";                                     \
        break;                                                 \
      case 95:                                                 \
        s = "EMULTIHOP (Reserved)";                            \
        break;                                                 \
      case 96:                                                 \
        s = "No message available on STREAM";                  \
        break;                                                 \
      case 97:                                                 \
        s = "ENOLINK (Reserved)";                              \
        break;                                                 \
      case 98:                                                 \
        s = "No STREAM resources";                             \
        break;                                                 \
      case 99:                                                 \
        s = "Not a STREAM";                                    \
        break;                                                 \
      case 100:                                                \
        s = "Protocol error";                                  \
        break;                                                 \
      case 101:                                                \
        s = "STREAM ioctl timeout";                            \
        break;                                                 \
      case 102:                                                \
        s = "Operation not supported on socket";               \
        break;                                                 \
      case 103:                                                \
        s = "Policy not found";                                \
        break;                                                 \
      case 104:                                                \
        s = "State not recoverable";                           \
        break;                                                 \
      case 105:                                                \
        s = "Previous owner died";                             \
        break;                                                 \
      case 106:                                                \
        s = "Interface output queue is full";                  \
        break;                                                 \
    }                                                          \
  })

#define ER_LINUKS(s, x)                                        \
  ({                                                           \
    switch (x) {                                               \
      case 1:                                                  \
        s = "Operation not permitted";                         \
        break;                                                 \
      case 2:                                                  \
        s = "No such file or directory";                       \
        break;                                                 \
      case 3:                                                  \
        s = "No such process";                                 \
        break;                                                 \
      case 4:                                                  \
        s = "Interrupted system call";                         \
        break;                                                 \
      case 5:                                                  \
        s = "I/O error";                                       \
        break;                                                 \
      case 6:                                                  \
        s = "No such device or address";                       \
        break;                                                 \
      case 7:                                                  \
        s = "Arg list too long";                               \
        break;                                                 \
      case 8:                                                  \
        s = "Exec format error";                               \
        break;                                                 \
      case 9:                                                  \
        s = "Bad file number";                                 \
        break;                                                 \
      case 10:                                                 \
        s = "No child processes";                              \
        break;                                                 \
      case 11:                                                 \
        s = "Try again";                                       \
        break;                                                 \
      case 12:                                                 \
        s = "Out of memory";                                   \
        break;                                                 \
      case 13:                                                 \
        s = "Permission denied";                               \
        break;                                                 \
      case 14:                                                 \
        s = "Bad address";                                     \
        break;                                                 \
      case 15:                                                 \
        s = "Block device required";                           \
        break;                                                 \
      case 16:                                                 \
        s = "Device or resource busy";                         \
        break;                                                 \
      case 17:                                                 \
        s = "File exists";                                     \
        break;                                                 \
      case 18:                                                 \
        s = "Cross-device link";                               \
        break;                                                 \
      case 19:                                                 \
        s = "No such device";                                  \
        break;                                                 \
      case 20:                                                 \
        s = "Not a directory";                                 \
        break;                                                 \
      case 21:                                                 \
        s = "Is a directory";                                  \
        break;                                                 \
      case 22:                                                 \
        s = "Invalid argument";                                \
        break;                                                 \
      case 23:                                                 \
        s = "File table overflow";                             \
        break;                                                 \
      case 24:                                                 \
        s = "Too many open files";                             \
        break;                                                 \
      case 25:                                                 \
        s = "Not a typewriter";                                \
        break;                                                 \
      case 26:                                                 \
        s = "Text file busy";                                  \
        break;                                                 \
      case 27:                                                 \
        s = "File too large";                                  \
        break;                                                 \
      case 28:                                                 \
        s = "No space left on device";                         \
        break;                                                 \
      case 29:                                                 \
        s = "Illegal seek";                                    \
        break;                                                 \
      case 30:                                                 \
        s = "Read-only file system";                           \
        break;                                                 \
      case 31:                                                 \
        s = "Too many links";                                  \
        break;                                                 \
      case 32:                                                 \
        s = "Broken pipe";                                     \
        break;                                                 \
      case 33:                                                 \
        s = "Math argument out of domain of func";             \
        break;                                                 \
      case 34:                                                 \
        s = "Math result not representable";                   \
        break;                                                 \
      case 35:                                                 \
        s = "Resource deadlock would occur";                   \
        break;                                                 \
      case 36:                                                 \
        s = "File name too long";                              \
        break;                                                 \
      case 37:                                                 \
        s = "No record locks available";                       \
        break;                                                 \
      case 38:                                                 \
        s = "Function not implemented";                        \
        break;                                                 \
      case 39:                                                 \
        s = "Directory not empty";                             \
        break;                                                 \
      case 40:                                                 \
        s = "Too many symbolic links encountered";             \
        break;                                                 \
      case 41:                                                 \
        s = "Operation would block";                           \
        break;                                                 \
      case 42:                                                 \
        s = "No message of desired type";                      \
        break;                                                 \
      case 43:                                                 \
        s = "Identifier removed";                              \
        break;                                                 \
      case 44:                                                 \
        s = "Channel number out of range";                     \
        break;                                                 \
      case 45:                                                 \
        s = "Level 2 not synchronized";                        \
        break;                                                 \
      case 46:                                                 \
        s = "Level 3 halted";                                  \
        break;                                                 \
      case 47:                                                 \
        s = "Level 3 reset";                                   \
        break;                                                 \
      case 48:                                                 \
        s = "Link number out of range";                        \
        break;                                                 \
      case 49:                                                 \
        s = "Protocol driver not attached";                    \
        break;                                                 \
      case 50:                                                 \
        s = "No CSI structure available";                      \
        break;                                                 \
      case 51:                                                 \
        s = "Level 2 halted";                                  \
        break;                                                 \
      case 52:                                                 \
        s = "Invalid exchange";                                \
        break;                                                 \
      case 53:                                                 \
        s = "Invalid request descriptor";                      \
        break;                                                 \
      case 54:                                                 \
        s = "Exchange full";                                   \
        break;                                                 \
      case 55:                                                 \
        s = "No anode";                                        \
        break;                                                 \
      case 56:                                                 \
        s = "Invalid request code";                            \
        break;                                                 \
      case 57:                                                 \
        s = "Invalid slot";                                    \
        break;                                                 \
      case 58:                                                 \
        s = "File locking deadlock error";                     \
        break;                                                 \
      case 59:                                                 \
        s = "Bad font file format";                            \
        break;                                                 \
      case 60:                                                 \
        s = "Device not a stream";                             \
        break;                                                 \
      case 61:                                                 \
        s = "No data available";                               \
        break;                                                 \
      case 62:                                                 \
        s = "Timer expired";                                   \
        break;                                                 \
      case 63:                                                 \
        s = "Out of streams resources";                        \
        break;                                                 \
      case 64:                                                 \
        s = "Machine is not on the network";                   \
        break;                                                 \
      case 65:                                                 \
        s = "Package not installed";                           \
        break;                                                 \
      case 66:                                                 \
        s = "Object is remote";                                \
        break;                                                 \
      case 67:                                                 \
        s = "Link has been severed";                           \
        break;                                                 \
      case 68:                                                 \
        s = "Advertise error";                                 \
        break;                                                 \
      case 69:                                                 \
        s = "Srmount error";                                   \
        break;                                                 \
      case 70:                                                 \
        s = "Communication error on send";                     \
        break;                                                 \
      case 71:                                                 \
        s = "Protocol error";                                  \
        break;                                                 \
      case 72:                                                 \
        s = "Multihop attempted";                              \
        break;                                                 \
      case 73:                                                 \
        s = "RFS specific error";                              \
        break;                                                 \
      case 74:                                                 \
        s = "Not a data message";                              \
        break;                                                 \
      case 75:                                                 \
        s = "Value too large for defined data type";           \
        break;                                                 \
      case 76:                                                 \
        s = "Name not unique on network";                      \
        break;                                                 \
      case 77:                                                 \
        s = "File descriptor in bad state";                    \
        break;                                                 \
      case 78:                                                 \
        s = "Remote address changed";                          \
        break;                                                 \
      case 79:                                                 \
        s = "Can not access a needed shared library";          \
        break;                                                 \
      case 80:                                                 \
        s = "Accessing a corrupted shared library";            \
        break;                                                 \
      case 81:                                                 \
        s = ".lib section in a.out corrupted";                 \
        break;                                                 \
      case 82:                                                 \
        s = "Attempting to link in too many shared libraries"; \
        break;                                                 \
      case 83:                                                 \
        s = "Cannot exec a shared library directly";           \
        break;                                                 \
      case 84:                                                 \
        s = "Illegal byte sequence";                           \
        break;                                                 \
      case 85:                                                 \
        s = "Interrupted system call should be restarted";     \
        break;                                                 \
      case 86:                                                 \
        s = "Streams pipe error";                              \
        break;                                                 \
      case 87:                                                 \
        s = "Too many users";                                  \
        break;                                                 \
      case 88:                                                 \
        s = "Socket operation on non-socket";                  \
        break;                                                 \
      case 89:                                                 \
        s = "Destination address required";                    \
        break;                                                 \
      case 90:                                                 \
        s = "Message too long";                                \
        break;                                                 \
      case 91:                                                 \
        s = "Protocol wrong type for socket";                  \
        break;                                                 \
      case 92:                                                 \
        s = "Protocol not available";                          \
        break;                                                 \
      case 93:                                                 \
        s = "Protocol not supported";                          \
        break;                                                 \
      case 94:                                                 \
        s = "Socket type not supported";                       \
        break;                                                 \
      case 95:                                                 \
        s = "Operation not supported on transport endpoint";   \
        break;                                                 \
      case 96:                                                 \
        s = "Protocol family not supported";                   \
        break;                                                 \
      case 97:                                                 \
        s = "Address family not supported by protocol";        \
        break;                                                 \
      case 98:                                                 \
        s = "Address already in use";                          \
        break;                                                 \
      case 99:                                                 \
        s = "Cannot assign requested address";                 \
        break;                                                 \
      case 100:                                                \
        s = "Network is down";                                 \
        break;                                                 \
      case 101:                                                \
        s = "Network is unreachable";                          \
        break;                                                 \
      case 102:                                                \
        s = "Network dropped connection because of reset";     \
        break;                                                 \
      case 103:                                                \
        s = "Software caused connection abort";                \
        break;                                                 \
      case 104:                                                \
        s = "Connection reset by peer";                        \
        break;                                                 \
      case 105:                                                \
        s = "No buffer space available";                       \
        break;                                                 \
      case 106:                                                \
        s = "Transport endpoint is already connected";         \
        break;                                                 \
      case 107:                                                \
        s = "Transport endpoint is not connected";             \
        break;                                                 \
      case 108:                                                \
        s = "Cannot send after transport endpoint shutdown";   \
        break;                                                 \
      case 109:                                                \
        s = "Too many references: cannot splice";              \
        break;                                                 \
      case 110:                                                \
        s = "Connection timed out";                            \
        break;                                                 \
      case 111:                                                \
        s = "Connection refused";                              \
        break;                                                 \
      case 112:                                                \
        s = "Host is down";                                    \
        break;                                                 \
      case 113:                                                \
        s = "No route to host";                                \
        break;                                                 \
      case 114:                                                \
        s = "Operation already in progress";                   \
        break;                                                 \
      case 115:                                                \
        s = "Operation now in progress";                       \
        break;                                                 \
      case 116:                                                \
        s = "Stale NFS file handle";                           \
        break;                                                 \
      case 117:                                                \
        s = "Structure needs cleaning";                        \
        break;                                                 \
      case 118:                                                \
        s = "Not a XENIX named type file";                     \
        break;                                                 \
      case 119:                                                \
        s = "No XENIX semaphores available";                   \
        break;                                                 \
      case 120:                                                \
        s = "Is a named type file";                            \
        break;                                                 \
      case 121:                                                \
        s = "Remote I/O error";                                \
        break;                                                 \
    }                                                          \
  })

#endif