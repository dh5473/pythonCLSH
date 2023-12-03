import logging


class Logger:
    def __init__(self, file_path):
        self.logger = logging.getLogger()

        if not self.logger.handlers:
            formatter = logging.Formatter(u'%(asctime)s [%(levelname)s] %(message)s')
            self.logger.setLevel(logging.INFO)

            file_handler = logging.FileHandler(filename=file_path)
            file_handler.setFormatter(formatter)
            self.logger.addHandler(file_handler)

    def info(self, context):
        self.logger.info(context)
    
    def error(self, context):
        self.logger.error(context)