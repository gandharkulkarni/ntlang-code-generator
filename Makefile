PROGS = rstr rstr_rec get_bitseq get_bitseq_signed pack_bytes unpack_bytes ntlang

RSTR_OBJS = rstr.o rstr_c.o rstr_s.o
RSTR_REC_OBJS = rstr_rec.o rstr_rec_c.o rstr_rec_s.o
GET_BITSEQ_OBJS = get_bitseq.o get_bitseq_s.o get_bitseq_c.o
GET_BITSEQ_SIGNED_OBJS = get_bitseq_signed.o\
						 get_bitseq_signed_c.o get_bitseq_c.o\
                         get_bitseq_signed_s.o get_bitseq_s.o
PACK_OBJS = pack_bytes.o pack_bytes_c.o pack_bytes_s.o
UNPACK_OBJS = unpack_bytes.o unpack_bytes_c.o unpack_bytes_s.o

NTLANG_OBJS = ntlang.o scan.o parse.o eval.o conv.o

OBJS = ${RSTR_OBJS} ${RSTR_REC_OBJS} \
	   ${GET_BITSEQ_OBJS} ${GET_BITSEQ_SIGNED_OBJS} \
       ${PACK_OBJS} ${UNPACK_OBJS} \
       ${NTLANG_OBJS}

CFLAGS = -g
ASFLAGS = -g

%.o: %.c
	gcc ${CFLAGS} -c -o $@ $<

%.o: %.s
	as ${ASFLAGS} -o $@ $<

all: ${PROGS}

rstr: ${RSTR_OBJS}
	gcc ${CFLAGS} -o $@ $^

rstr_rec: ${RSTR_REC_OBJS}
	gcc ${CFLAGS} -o $@ $^

get_bitseq: ${GET_BITSEQ_OBJS}
	gcc ${CFLAGS} -o $@ $^

get_bitseq_signed: ${GET_BITSEQ_SIGNED_OBJS}
	gcc ${CFLAGS} -o $@ $^

pack_bytes: ${PACK_OBJS}
	gcc ${CFLAGS} -o $@ $^

unpack_bytes: $(UNPACK_OBJS)
	gcc ${CFLAGS} -o $@ $^

ntlang : ${NTLANG_OBJS} ntlang.h
	gcc ${CFLAGS} -o $@ ${NTLANG_OBJS}

clean:
	rm -rf ${PROGS} ${OBJS}
