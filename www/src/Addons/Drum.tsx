import React, { useContext } from 'react';
import { useTranslation } from 'react-i18next';
import { FormCheck, Row } from 'react-bootstrap';
import * as yup from 'yup';

import Section from '../Components/Section';
import FormSelect from '../Components/FormSelect';
import { ANALOG_PINS } from '../Data/Buttons';
import AnalogPinOptions from '../Components/AnalogPinOptions';
import { AppContext } from '../Contexts/AppContext';
import FormControl from '../Components/FormControl';

export const drumScheme = {
	DrumEnabled: yup.number().required().label('Drum Enabled'),
	drumDonLeftPin: yup
		.number()
		.label('Don Left Pin')
		.validatePinWhenValue('DrumEnabled'),
	drumDonLeftThresh: yup
		.number()
		.min(0).max(4095)
		.label('Don Left Threshold'),
	drumDonLeftThreshForce: yup
		.number()
		.min(0).max(4095)
		.label('Don Left Threshold (Strong)'),
	drumDonRightPin: yup
		.number()
		.label('Don Right Pin')
		.validatePinWhenValue('DrumEnabled'),
	drumDonRightThresh: yup
		.number()
		.min(0).max(4095)
		.label('Don Right Threshold'),
	drumDonRightThreshForce: yup
		.number()
		.min(0).max(4095)
		.label('Don Right Threshold (Strong)'),
	drumKaLeftPin: yup
		.number()
		.label('Ka Left Pin')
		.validatePinWhenValue('DrumEnabled'),
	drumKaLeftThresh: yup
		.number()
		.min(0).max(4095)
		.label('Ka Left Threshold'),
	drumKaLeftThreshForce: yup
		.number()
		.min(0).max(4095)
		.label('Ka Left Threshold (Strong)'),
	drumKaRightPin: yup
		.number()
		.label('Ka Right Pin')
		.validatePinWhenValue('DrumEnabled'),
	drumKaRightThresh: yup
		.number()
		.min(0).max(4095)
		.label('Ka Right Threshold'),
	drumKaRightThreshForce: yup
		.number()
		.min(0).max(4095)
		.label('Ka Right Threshold (Strong)'),
	drumSwitchPin: yup
		.number()
		.label('Switch Pin')
		.validatePinWhenValue('DrumEnabled'),
};

export const drumState = {
	DrumEnabled: 0,
	drumDonLeftPin: -1,
	drumDonLeftThresh: 30,
	drumDonLeftThreshForce: 2000,
	drumDonRightPin: -1,
	drumDonRightThresh: 30,
	drumDonRightThreshForce: 2000,
	drumKaLeftPin: -1,
	drumKaLeftThresh: 10,
	drumKaLeftThreshForce: 1000,
	drumKaRightPin: -1,
	drumKaRightThresh: 10,
	drumKaRightThreshForce: 1000,
	drumSwitchPin: -1,
};

// FIXME: Default values are 0 for strong thresholds, even though everything else seemingly works

const Drum = ({ values, errors, handleChange, handleCheckbox }) => {
	const { usedPins } = useContext(AppContext);
	const { t } = useTranslation();
	const availableAnalogPins = ANALOG_PINS.filter(
		(pin) => !usedPins?.includes(pin),
	);

	return (
		<Section title={t('AddonsConfig:drum-header-text')}>
			<div id="DrumOptions" hidden={!values.DrumEnabled}>
				<Row className="mb-3">
					<FormSelect
						label={t('AddonsConfig:drum-don-left-pin')}
						name="drumDonLeftPin"
						className="form-select-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumDonLeftPin}
						error={errors.drumDonLeftPin}
						isInvalid={errors.drumDonLeftPin}
						onChange={handleChange}
					>
						<AnalogPinOptions />
					</FormSelect>
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-don-left-thresh')}
						name="drumDonLeftThresh"
						className="form-control-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumDonLeftThresh}
						error={errors.drumDonLeftThresh}
						isInvalid={errors.drumDonLeftThresh}
						onChange={handleChange}
						min={0}
						max={4095}
					/>
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-don-left-thresh-force')}
						name="drumDonLeftThreshForce"
						className="form-control-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumDonLeftThreshForce}
						error={errors.drumDonLeftThreshForce}
						isInvalid={errors.drumDonLeftThreshForce}
						onChange={handleChange}
						min={0}
						max={4095}
					/>
				</Row>

				<Row className="mb-3">
					<FormSelect
						label={t('AddonsConfig:drum-don-right-pin')}
						name="drumDonRightPin"
						className="form-select-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumDonRightPin}
						error={errors.drumDonRightPin}
						isInvalid={errors.drumDonRightPin}
						onChange={handleChange}
					>
						<AnalogPinOptions />
					</FormSelect>
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-don-right-thresh')}
						name="drumDonRightThresh"
						className="form-control-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumDonRightThresh}
						error={errors.drumDonRightThresh}
						isInvalid={errors.drumDonRightThresh}
						onChange={handleChange}
						min={0}
						max={4095}
					/>
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-don-right-thresh-force')}
						name="drumDonRightThreshForce"
						className="form-control-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumDonRightThreshForce}
						error={errors.drumDonRightThreshForce}
						isInvalid={errors.drumDonRightThreshForce}
						onChange={handleChange}
						min={0}
						max={4095}
					/>
				</Row>

				<Row className="mb-3">
					<FormSelect
						label={t('AddonsConfig:drum-ka-left-pin')}
						name="drumKaLeftPin"
						className="form-select-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumKaLeftPin}
						error={errors.drumKaLeftPin}
						isInvalid={errors.drumKaLeftPin}
						onChange={handleChange}
					>
						<AnalogPinOptions />
					</FormSelect>
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-ka-left-thresh')}
						name="drumKaLeftThresh"
						className="form-control-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumKaLeftThresh}
						error={errors.drumKaLeftThresh}
						isInvalid={errors.drumKaLeftThresh}
						onChange={handleChange}
						min={0}
						max={4095}
					/>
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-ka-left-thresh-force')}
						name="drumKaLeftThreshForce"
						className="form-control-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumKaLeftThreshForce}
						error={errors.drumKaLeftThreshForce}
						isInvalid={errors.drumKaLeftThreshForce}
						onChange={handleChange}
						min={0}
						max={4095}
					/>
				</Row>

				<Row className="mb-3">
					<FormSelect
						label={t('AddonsConfig:drum-ka-right-pin')}
						name="drumKaRightPin"
						className="form-select-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumKaRightPin}
						error={errors.drumKaRightPin}
						isInvalid={errors.drumKaRightPin}
						onChange={handleChange}
					>
						<AnalogPinOptions />
					</FormSelect>
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-ka-right-thresh')}
						name="drumKaRightThresh"
						className="form-control-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumKaRightThresh}
						error={errors.drumKaRightThresh}
						isInvalid={errors.drumKaRightThresh}
						onChange={handleChange}
						min={0}
						max={4095}
					/>
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-ka-right-thresh-force')}
						name="drumKaRightThreshForce"
						className="form-control-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumKaRightThreshForce}
						error={errors.drumKaRightThreshForce}
						isInvalid={errors.drumKaRightThreshForce}
						onChange={handleChange}
						min={0}
						max={4095}
					/>
				</Row>

				<Row className="mb-3">
					<FormControl
						type="number"
						label={t('AddonsConfig:drum-switch-pin')}
						name="drumSwitchPin"
						className="form-select-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.drumSwitchPin}
						error={errors.drumSwitchPin}
						isInvalid={errors.drumSwitchPin}
						onChange={handleChange}
						min={-1}
						max={29}
					/>
				</Row>
			</div>
			<FormCheck
				label={t('Common:switch-enabled')}
				type="switch"
				id="DrumButton"
				reverse
				isInvalid={false}
				checked={Boolean(values.DrumEnabled)}
				onChange={(e) => {
					handleCheckbox('DrumEnabled', values);
					handleChange(e);
				}}
			/>
		</Section>
	);
};

export default Drum;
