#ifndef __OPT3001_H__
#define __OPT3001_H__
class opt3001
{
	public:
		opt3001();
		~opt3001();
		void init(void);
		float read_lux(void);
	private:
		int fd;
};
#endif
