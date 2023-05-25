# import the necessary packages
from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
from tensorflow.keras.preprocessing.image import img_to_array
from tensorflow.keras.models import load_model
from imutils.video import VideoStream
import numpy as np
import imutils
import cv2
import os
from PIL import Image
from numpy import asarray
from mtcnn.mtcnn import MTCNN
from numpy import load
from numpy import expand_dims
from numpy import asarray
from keras.models import load_model
import numpy as np
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import Normalizer
from mark_attendence import markAttendance


def detect_and_predict_mask(frame, faceNet, Clf_Model):
	# grab the dimensions of the frame and then construct a blob
	# from it
	image = frame
	image = Image.fromarray(image)
	print(type(image))
	# pass the blob through the network and obtain the face detections
	image = image.convert('RGB')
	# convert to array
	pixels = asarray(image)
	# create the detector, using default weights
	detector = MTCNN()
	# detect faces in the image
	results = detector.detect_faces(pixels)

	# initialize our list of faces, their corresponding locations,
	# and the list of predictions from our face mask network
	faces = []
	locs = []
	preds = []
	face_Embeddings = []
	# loop over the detections
	for result in results:
		# extract the confidence (i.e., probability) associated with
		# the detection
		confidence = result['confidence']
		# filter out weak detections by ensuring the confidence is
		# greater than the minimum confidence
		if confidence > 0.5:
			# compute the (x, y)-coordinates of the bounding box for
			# the object
			# # ensure the bounding boxes fall within the dimensions of
			# # the frame

			box = result['box']
			x1, y1, width, height = box
			x1, y1 = abs(x1), abs(y1)
			x2, y2 = x1 + width, y1 + height
			# extract the face
			face = pixels[y1:y2, x1:x2]
			image = Image.fromarray(face)
			image = image.resize((160,160))
			face = asarray(image)
			# add the face and bounding boxes to their respective
			# lists
			faces.append(face)
			locs.append((x1, y1, x2, y2))
	# all the faces of the Image
	faces.extend(faces)
	faces = asarray(faces)

	for f in faces: 
		# scale pixel values
		face_pixels = np.float32(f)
		# standardize pixel values across channels (global)
		mean, std = face_pixels.mean(), face_pixels.std()
		face_pixels = (face_pixels - mean) / std
		# transform face into one sample
		samples = expand_dims(face_pixels, axis=0)
		# make prediction to get embedding
		yhat = faceNet.predict(samples)
		embedding = yhat[0]
		face_Embeddings.append(embedding)

	in_encoder = Normalizer(norm='l2')
	if len(face_Embeddings) > 0:
		# for faster inference we'll make batch predictions on *all*
		# faces at the same time rather than one-by-one predictions
		# in the above `for` loop
		# faces = np.array(faces, dtype="float32")
		# preds = maskNet.predict(faces, batch_size=32)
		face_Embeddings = asarray(face_Embeddings)
		# normalize input vectors
		face_Embeddings = in_encoder.transform(face_Embeddings)
		preds = Clf_Model.predict(face_Embeddings, batch_size=16)
	# only make a predictions if at least one face was detected

	# return a 2-tuple of the face locations and their corresponding
	# locations
	return (locs, preds)

# load our serialized face detector model from disk
base = r'D:\DeepLearning\Udacity\Graduation_project\Face-recognition'
FaceNet_path = r"D:\DeepLearning\Udacity\Graduation_project\Face-recognition\facenet_keras.h5"

faceNet = load_model(FaceNet_path)
print("FaceNet Loaded")
# load the face embedding classification detector model from disk
Clf_Model = load_model(os.path.join(base , "Classification.hdf5"))
print("Classification model loaded")

# getting our labbels
data = load(r'D:\DeepLearning\Udacity\Graduation_project\Face-recognition\Dataset-faces-embeddings.npz', allow_pickle=True)
trainy=  data['arr_1']
# label encode targets
out_encoder = LabelEncoder()
out_encoder.fit(trainy)
trainy = out_encoder.transform(trainy)
# initialize the video stream
print("[INFO] starting video stream...")
vs = VideoStream(src=0).start()

# loop over the frames from the video stream
while True:
	# grab the frame from the threaded video stream and resize it
	# to have a maximum width of 400 pixels
	frame = vs.read()
	frame = imutils.resize(frame, width=700)
	
	# detect faces in the frame
	cv2.imshow("Frame", frame)
	(locs, preds) = detect_and_predict_mask(frame, faceNet, Clf_Model)
	
	# loop over the detected face locations and their corresponding
	# locations
	cv2.imshow("Frame", frame)
	for (box, pred) in zip(locs, preds):
		# unpack the bounding box and predictions
		(startX, startY, endX, endY) = box
		# (stuedent index) = np.argmax(pred)
		class_index = np.argmax(pred)
		
		# determine the class label and color we'll use to draw
		# the bounding box and text
		cv2.imshow("Frame", frame)
		class_probability = pred[class_index] * 100
		predict_names = out_encoder.inverse_transform(np.array([class_index]))
		cv2.imshow("Frame", frame)

		# color = (0, 255, 0) if label == "Mask" else (0, 0, 255)
		color = (0, 255, 0)
		# include the probability in the label
		label = "{}: {:.2f}%".format(predict_names[0], class_probability)
		# display the label and bounding box rectangle on the output
		# frame
		cv2.putText(frame, label, (startX, startY - 10),
			cv2.FONT_HERSHEY_SIMPLEX, 0.45, color, 2)
		cv2.rectangle(frame, (startX, startY), (endX, endY), color, 2)
		markAttendance(predict_names[0])
	# show the output frame
	cv2.imshow("Frame", frame)
	key = cv2.waitKey(1) & 0xFF

	# if the `q` key was pressed, break from the loop
	if key == ord("q"):
		break

# do a bit of cleanup
cv2.destroyAllWindows()
vs.stop()